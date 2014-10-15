#include "std_lib_facilities.h"
#include<set>

// code examples for containers and iterators -- two separate programs.
// Uncomment one at a time and compile and run to see what they do
/*
int main()
{
  // example 1
  // 1) initialize two containers, vector and list, each with five integers
  // 2) use iterators to print out the entire sequence for each
  // 3) use iterators to find the max value of the stored values for each

  // initialize vector
  //  int size=5;
  //  vector<int> values(size);
  //  for (int i=0; i<size; ++i) {
  //  values[i] = i+1;
  //  }
  // use the vector container function to populate it
  vector<int> values;
  values.push_back(5);
  values.push_back(2);
  values.push_back(3);
  values.push_back(4);
  values.push_back(1);

  // initialize list
  // use the list container function to populate it
  list<int> values2;
  values2.push_back(10);
  values2.push_back(7);
  values2.push_back(8);
  values2.push_back(9);
  values2.push_back(6);

  // print values
  vector<int>::iterator current = values.begin();
  list<int>::iterator current2 = values2.begin();

  // for the vector first
  cout << "Print vector without iterator first:\n";
  for (int i=0; i<values.size(); ++i) {
    cout << values[i] << " ";
  }
  cout << endl;

  cout << "Print vector with iterator:\n";
  for (current = values.begin(); current != values.end(); ++current) {
    cout << *current << " ";
  }
  cout << endl;

  // for the list
  cout << "Print list with iterator:\n";
  for (current2 = values2.begin(); current2 != values2.end(); ++current2) {
    cout << *current2 << " ";
  }
  cout << endl;

  // find the max values in each data sequence  using iterators
  // for the vector first
  current = values.begin();
  int max = *current++;
  //  current++;
  // end() gives one past the last element
  while (current != values.end()) 
    {
      if (*current > max)
	{
	  max = *current;
	}
      current++;
    }
  cout << "Max in vector: " << max << endl;
  
  // now for the list
  current2 = values2.begin();
  int max2 = *current2++;
  //  current2++;

  while (current2 != values2.end())
    {
      if (*current2 > max2)
	{
	  max2 = *current2;
	}
      current2++;
    }
  cout << "Max in list: " << max2 << endl;
  cout << "------------------------------------------------------------\n";

  //-----------------------------------------------------------------------
  // example 2
  // using iterators on other types of containers: list, set, multiset
  // different container types support different functions: lists and vectors
  // support push_back(), while the set container support insert() but not
  // push_back()

  // list container for character elements
  list<char> lst;

  // append elements from 'A' to 'Z' to the list lst container (the list
  // container does not have an insert() function)
  for(char chs='A'; chs<='Z'; ++chs)
    // lst.push_back(chs);
    lst.insert(lst.end(), chs); // since insert() is also defined, we use that
				// for a change

  // iterate over all elements and print, separated by space
  list<char>::const_iterator pos;
  cout << "Print list containing characters of the alphabet using iterators\n";
  for(pos = lst.begin(); pos != lst.end(); ++pos)
    cout << *pos << ' ';
  cout << endl;

  // set container of int data type
  set<int> tst;

  // insert elements (push_back() is not defined)
  tst.insert(12);
  tst.insert(21);
  tst.insert(32);
  tst.insert(31);
  tst.insert(9);
  tst.insert(14);
  tst.insert(21);
  tst.insert(31);
  tst.insert(7);

  // iterate over all elements and print, separated by space
  set<int>::const_iterator pos2;

  cout << "Print set containing 7 unique integers using iterators\n";
  for(pos2 = tst.begin(); pos2 != tst.end(); ++pos2)
    cout << *pos2 << ' ';
  cout << endl;  

  // multiset container of int data type
  multiset<int> tst2;
  // insert elements
  tst2.insert(12);
  tst2.insert(21);
  tst2.insert(32);
  tst2.insert(31);
  tst2.insert(9);
  tst2.insert(14);
  tst2.insert(21);
  tst2.insert(31);
  tst2.insert(7);

  // iterate over all elements and print, separated by space
  multiset<int>::const_iterator pos3;

  cout << "Print multiset containing 9 total (7 unique) unique integers using iterators\n";
  for(pos3 = tst2.begin(); pos3 != tst2.end(); ++pos3)
    cout << *pos3 << ' ';
  cout << endl;
  cout << "------------------------------------------------------------\n";  
}
*/
//-----------------------------------------------------------------------
// use of list container containing elements of type defined by user
class AAA {
  friend ostream & operator<<(ostream &, const AAA &);
public:
  int x;
  int y;
  float z;
  
  AAA(); // constructor
  AAA(const AAA &); // copy constructor
  ~AAA(){};
  AAA &operator=(const AAA &rhs);
  int operator==(const AAA &rhs) const;
  int operator<(const AAA &rhs) const;
};

AAA::AAA()   // Constructor
{
  x = 0;
  y = 0;
  z = 0;
}

AAA::AAA(const AAA &copyin)   // Copy constructor to handle pass by value
{                            
  x = copyin.x;
  y = copyin.y;
  z = copyin.z;
}

ostream & operator<<(ostream & output, const AAA & aaa)
{
  output << aaa.x << ' ' << aaa.y << ' ' << aaa.z << endl;
  return output;
}

AAA& AAA::operator=(const AAA & rhs)
{
  this->x = rhs.x;
  this->y = rhs.y;
  this->z = rhs.z;
  return *this;
}

int AAA::operator==(const AAA &rhs) const
{
  if( this->x != rhs.x) return 0;
  if( this->y != rhs.y) return 0;
  if( this->z != rhs.z) return 0;
  return 1;
}

// This function is required for built-in STL list functions like sort
int AAA::operator<(const AAA &rhs) const
{
  if(this->x == rhs.x && this->y == rhs.y && this->z < rhs.z) return 1;
  if(this->x == rhs.x && this->y < rhs.y) return 1;
  if(this->x < rhs.x ) return 1;
  return 0;
}

int main()
{
  list<AAA> L;
  AAA Ablob ;
 
  Ablob.x=7;
  Ablob.y=2;
  Ablob.z=4.2355;
  L.push_back(Ablob);  // Insert a new element at the end
 
  Ablob.x=5;
  L.push_back(Ablob);  // Object passed by value. Uses default member-wise copy constructor
  Ablob.z=3.2355;
  L.push_back(Ablob);

  Ablob.x=3;
  Ablob.y=7;
  Ablob.z=7.2355;
  L.push_back(Ablob);

  list<AAA>::iterator i;

  cout << "Print x for each element in the list:\n";
  for(i=L.begin(); i != L.end(); ++i) 
    cout << (*i).x << " "; // print member
  cout << endl;
  cout << endl;

  cout << "Print (x,y,z) for each element in the list:\n";
  for(i=L.begin(); i != L.end(); ++i) 
    cout << *i; // print with overloaded operator
  cout << endl;

  cout << "Sorted: " << endl;
  L.sort();
  for(i=L.begin(); i != L.end(); ++i) 
    cout << *i; // print with overloaded operator
  cout << endl;
}
