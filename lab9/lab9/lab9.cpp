#include "../../std_lib_facilities.h"

using namespace std;
template <class T>
class LinkedList
{
	LinkedList* next;
	bool endOfList;
	T element;
public:
	LinkedList(T e)
		: element(e), endOfList(true) {}
	LinkedList(LinkedList* x, T e)
		: element(e), next(x), endOfList(true)
	{
		x->setEnd(false);
		x->setLink(this);
	}
	void setEnd(bool x) { endOfList = x;}
	void setLink(LinkedList* p) { next = p;}
	bool isEnd() { return endOfList;}
	T getElement() { return element;}
	LinkedList* getLink() { return next;}
};

// A generic function that iterates through a linked list from the supplied link to the end
template <class T>
void iter(LinkedList<T> *x)
{
  // We will use the variable y as our "iterator" to parse through the LinkedList.
  // Essentially: y points to one link, prints out that links value, and then grabs the
  // next link based on what y is currently attached to.
  LinkedList<T> *y = x;
  while (!y->isEnd())
    {
      cout << y->getElement() << " ";
      y = y->getLink();
    }
  
  // the last element is printed here, not in the while loop
  cout << y->getElement() << endl;
}

int main() {
  // the following is a test example using strings
  LinkedList<string> a("Hello,");
  LinkedList<string> b(&a, "world!");
  LinkedList<string> c(&b, "Welcome to the linked lists!");
  LinkedList<string> d(&c, "They are actually pretty powerful!");

  // calls the iterator to output all values in the linked list from A to the end.
  iter(&a);

  // showcases how we can use a vector to store dynamically created template objects, in this case LinkedList<int>
  vector< LinkedList<int>* > v;
  v.push_back(new LinkedList<int>(1));
  for (int i = 2; i <= 10; i++) {
    // tell the next LinkedList object we are creating that it is linked with the previous one (v[v.size()-1])
    v.push_back(new LinkedList<int>(v[v.size()-1], i));
  }

  // calls iter at the start of our vector of LinkedList<int>
  iter(v[0]);

  // calls iter in the middle of the vector
  iter(v[4]);
}