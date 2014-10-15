#include "std_lib_facilities.h"

// "List" is a container with the iterator that provides functions to iterate over it
//--------------------------------------------------------------------------------------------------------------------
// A link, just like we used while discussing doubly-linked lists

template<class Elem> struct Link {
  Link* prev;
  Link* succ;
  Elem val;
  Link (const Elem& v, Link* p=0, Link* s=0) : val(v), prev(p), succ(s) {}
};
//--------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------
// The List class, iterator is a member class

template<class Elem> class List {
private:
  Link<Elem>* first;
  Link<Elem>* last; // one beyond the last link
public:
  List () : first(0), last(new Link<Elem>(*(new Elem))) {} // create a sentinal node
  //  ~List ();  // iterate over all elements and deallocate them

  class iterator;
  iterator begin () { return iterator(first); }  // iterator to first element
  iterator end () { return iterator(last); }     // iterator to one beyond last element
  iterator insert (const iterator& p, const Elem& v)   // insert v before the element pointed to by p
  {
    Link<Elem>* n = p.insert(v);
    if (first == 0) first = n;
    return iterator(n);
  }
  iterator erase (iterator p)                   // return the iterator to the element after p
  {
    return iterator(p.erase());
  }
};
//--------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------
// iterator class
template<class Elem> class List<Elem>::iterator {
private:
  Link<Elem>* curr;
public:
  iterator (Link<Elem>* p) : curr(p) {}
  Link<Elem>* erase (); // return the iterator to the element after this
  Link<Elem>* insert (Elem e) const;
  Elem& operator*() { return curr->val; }
  iterator& operator++() { curr = curr->succ; return *this; }
  bool operator== (const iterator& b) const { return curr == b.curr; }
  bool operator!= (const iterator& b) const { return curr != b.curr; }
};

template<class Elem> Link<Elem>* List<Elem>::iterator::erase ()
{
  if (curr->succ) curr->succ->prev = curr->prev;
  if (curr->prev) curr->prev->succ = curr->succ;
  return curr->succ;
}

// Insert v before the element pointed to by this iterator
template<class Elem> Link<Elem>* List<Elem>::iterator::insert (Elem v) const
{
  Link<Elem>* n = new Link<Elem>(v);
  n->succ = curr;
  if (curr->prev) curr->prev->succ = n;
  n->prev = curr->prev;
  curr->prev = n;
  return n;
}
//--------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------
// A template function to iterate over a container -- tested in main() using a list as well as an array

template <class Iter> Iter high (Iter first, Iter last)
{
  Iter max = first;
  for (Iter p = first; p != last; ++p)
    if (*max < *p) max = p;
  return max;
}
//--------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------
int main ()
{
  List<int> myList;
  myList.insert(myList.end(), 10);
  List<int>::iterator twenty = myList.insert(myList.end(), 20);
  myList.insert(myList.insert(myList.end(), 30), 40);

  cout << "Initial list: ";
  for (List<int>::iterator i = myList.begin(); i != myList.end(); ++i)
    cout << *i << " ";
  cout << endl;

  cout << "Twenty = " << *twenty << endl;
  myList.erase(twenty);

  cout << "After deleting twenty: ";
  for (List<int>::iterator i = myList.begin(); i != myList.end(); ++i)
    cout << *i << " ";
  cout << endl;

  // Computing the max
  int max = -1;
  for (List<int>::iterator i = myList.begin(); i != myList.end(); ++i)
    if (max < *i) max = *i;
  cout << "Max (inlined) = " << max << endl;

  // Use the template function high to compute the max of the list
  List<int>::iterator high_val = high<List<int>::iterator>(myList.begin(), myList.end());
  cout << "Max = " << *high_val << endl;

  // This verifies that an iterator is nothing but a generalized pointer
  int A[5] = {1, 2, 5, 3, 4};
  cout << "Array max = " << *high<int*>(&A[0], &A[5]) << endl;
}
//--------------------------------------------------------------------------------------------------------------------
