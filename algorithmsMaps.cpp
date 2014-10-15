#include "std_lib_facilities.h"
#include <map>
#include <string.h>

// Multiple program examples in this file.  Uncomment one at a time to see what
// they do

//-----------------------------------------------------------------------
/* Simple map usage -- map is much more efficient than using arrays
int main()
{
   map<int, string> Employees;

   // assignment using array index notation
   Employees[5234] = "Mike C.";
   Employees[3374] = "Charlie M.";
   Employees[1923] = "David D.";
   Employees[7582] = "John A.";
   Employees[5328] = "Peter Q.";

   cout << "Employees[3374]=" << Employees[3374] << endl << endl;

   cout << "Map size: " << Employees.size() << endl;

   cout << "Print keys and values:\n";
   for(map<int,string>::iterator ii=Employees.begin(); ii!=Employees.end(); ++ii) {
     // first is value, second is key
     cout << (*ii).first << ": " << (*ii).second << endl;
   }

   cout << "\nPrint keys and values using pointers:\n";
   for(map<int,string>::iterator ii=Employees.begin(); ii!=Employees.end(); ++ii) {
     cout << ii->first << ": " << ii->second << endl;
   }
}
*/

//-----------------------------------------------------------------------
 /* Similar to previous example, but this time, using strings as keys -- various ways of populating a map are
    illustrated 
int main()
{
  map<string, int> Employees;

  // 1) Assignment using array index notation
   Employees["Mike C."] = 5234;
   Employees["Charlie M."] = 3374;

   // 2) Assignment using member function insert() and STL pair container
   Employees.insert(std::pair<string,int>("David D.",1923));

   // 3) Assignment using member function insert() and "value_type()".  value_type() is similar to pair, except that
   // the first argument is a const
   Employees.insert(map<string,int>::value_type("John A.",7582));

   // 4) Assignment using member function insert() and "make_pair()"
   Employees.insert(std::make_pair("Peter Q.",5328));

   cout << "Map size: " << Employees.size() << endl;

   for(map<string, int>::iterator ii=Employees.begin(); ii!=Employees.end(); ++ii) {
       cout << (*ii).first << ": " << (*ii).second << endl;
   }
}
 */

//-----------------------------------------------------------------------
  /* The first element in a map (key) can be a class or even another STL container such as a pair. If using a class, the
     class must provide an overloaded "equals" (=) and "less than" operator (<). Thus using "char" instead of "string"
     requires the use of a comparison function, as illustrated in the following program.  Note that "cmp_str" in the
     following program is a "function object".  Function objects are classes that have the function operator, (),
     overloaded. These function or function objects usually take one or two parameters and return a boolean, or
     true/false value. A function that returns a boolean value is also called a
     predicate.

struct cmp_str {
  bool operator()(const char *a, const char *b)
   {
     return ::strcmp(a, b) < 0;
   }
};

int main()
{
  // notice the third template argument to map
  map<char *, int, cmp_str> Employees;
  // Examples of assigning map container contents

   // 1) Assignment using array index notation
   Employees["Mike C."] = 5234;
   Employees["Charlie M."] = 3374;
 
   // 2) Assignment using member function insert() and STL pair
   Employees.insert(std::pair<char *,int>("David D.",1923));

   // 3) Assignment using member function insert() and "value_type()"
   Employees.insert(map<char *,int>::value_type("John A.",7582));

   // 4) Assignment using member function insert() and "make_pair()"
   Employees.insert(std::make_pair((char *)"Peter Q.",5328));

   cout << "Map size: " << Employees.size() << endl;

   for(map<char *, int, cmp_str>::iterator ii=Employees.begin(); ii!=Employees.end(); ++ii) {
       cout << (*ii).first << ": " << (*ii).second << endl;
   }
}
*/

//-----------------------------------------------------------------------
/* STL multimap example -- duplicate keys allowd */

int main()
{
  // Compare (<) function not required since it is built into string class.
  // else declaration would comparison function in multimap definition.
  // i.e. multimap<string, int, compare> m;

  multimap<string, int> m;
  m.insert(pair<string, int>("a", 1));
  m.insert(pair<string, int>("c", 2));
  m.insert(pair<string, int>("b", 3));
  m.insert(pair<string, int>("b", 4));
  m.insert(pair<string, int>("a", 5));
  m.insert(pair<string, int>("b", 6));

  cout << "Number of elements with key a: " << m.count("a") << endl;
  cout << "Number of elements with key b: " << m.count("b") << endl;
  cout << "Number of elements with key c: " << m.count("c") << endl;
  cout << "Elements in m: " << endl;

  for (multimap<string, int>::iterator it = m.begin(); it != m.end(); ++it) {
       cout << "  [" << (*it).first << ", " << (*it).second << "]" << endl;
   }

   pair<multimap<string, int>::iterator, multimap<string, int>::iterator> ppp;

   // equal_range(b) returns pair<iterator,iterator> representing the range
   // of element with key b
   ppp = m.equal_range("b");

   // Loop through range of maps of key "b"
   cout << endl << "Range of \"b\" elements:" << endl;
   for (multimap<string, int>::iterator it2 = ppp.first; it2 != ppp.second; ++it2) {
       cout << "  [" << (*it2).first << ", " << (*it2).second << "]" << endl;
   }

   m.clear();
}


//-----------------------------------------------------------------------
 /*  Use of the count algorithm with the vector container 

bool less (const int i) {
    return i < 25;
}

bool more (const int i) {
    return i > 25;
}

int main( )
{
    // Create an empty vector
    vector<int> v1;

    // Add numbers to vector
    v1.push_back(12);
    v1.push_back(25);
    v1.push_back(25);
    v1.push_back(35);
    v1.push_back(45);

    // Finds the number of elements equal to 25
    int quantity = count(v1.begin(), v1.end(), 25);

    cout << quantity << " elements equal to 25" << endl;

    // Finds the number of elements less than 25
    quantity = count_if(v1.begin(), v1.end(), ::less);

    cout << quantity << " elements less than 25" << endl;

    // Finds the number of elements greater than 25
    quantity = count_if(v1.begin(), v1.end(), more);

    cout << quantity << " elements greater than 25" << endl;
}
*/
