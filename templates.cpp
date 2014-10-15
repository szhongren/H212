#include "std_lib_facilities.h"

// multiple template-related programs in this file, separated
// by /////////
// uncomment one at a time and look at the leading comments to understand the
// concept being demonstrated

/////////////////////////////////////////////////////////////////
/* functions specified for each data type */

int square(int x)
{
  return x*x;
};

float square(float x)
{
  return x*x;
};

double square(double x)
{
  return x*x;
};

int main() 
{
  int i, ii;
  float x, xx;
  double y, yy;

  i = 2;
  x = 2.2;
  y = 2.2;

  ii = square(i);
  cout << i << ": " << ii << endl;

  xx = square(x);
  cout << x << ": " << xx << endl;

  yy = square(y);
  cout << y << ": " << yy << endl;
}


/////////////////////////////////////////////////////////////////

/* use templates (as described in lecture, using classes)  to accomplish the
   same thing 

template <class T> class function {
public: 
  int value;
  function() : value(0) {}; // default constructor
  T square(T x); // returns the square of the input parameter
};

template <class T> T function<T>::square(T x)
{
  T result;
  result = x*x;
  return result;
}

int main()
{
  function<int> foo;
  function<float> foo2;
  function<double> foo3;

  int i, ii;
  float x, xx;
  double y, yy;
  
  i = 2;
  x = 2.2;
  y = 2.2;

  ii = foo.square(i);
  cout << i << ": " << ii << endl;

  xx = foo2.square(x);
  cout << x << ": " << xx << endl;
  
  yy = foo3.square(y);
  cout << y << ": " << yy << endl; 
}
*/

/////////////////////////////////////////////////////////////////

/* templates can be used without classes as well 

template <class T> T square(T x)
{
  T result;
  result = x*x;
  return result;
}

int main()
{
  int i, ii;
  float x, xx;
  double y, yy;

  i = 2;
  x = 2.2;
  y = 2.2;

  ii = square<int>(i);
  cout << i << ": " << ii << endl;

  xx = square<float>(x);
  cout << x << ": " << xx << endl;
  
  // explicit use of template
  yy = square<double>(y);
  cout << y << ": " << yy << endl; 

  // implicit use of template
  yy = square(y);
  cout << y << ": " << yy << endl; 
}
*/

/////////////////////////////////////////////////////////////////

/* template specialization

template <class T> T square(T x)
{
  T result;
  result = x*x;
  return result;
}

// a specialized square function defined in the context of strings
template <> string square(string ss)
{
  return (ss+ss);
}

int main()
{
  int i = 2, ii;
  string ww("Aaa");

  // the general square function will be called
  ii = square<int>(i);
  cout << i << ": " << ii << endl;

  // specialized square for strings will be called
  cout << square<string>(ww) << endl;
}
*/

/////////////////////////////////////////////////////////////////

/*  class template specialization -- changing the running example used in the
    previous programs in this file

template <class T> class mycontainer {
  T element;
public:
  mycontainer (T arg) {element=arg;}
  T increase () {return ++element;}
};

// class template specialization
template <> class mycontainer <char> {
  char element;
public:
  mycontainer (char arg) {element=arg;}
  char uppercase ()
  {
    if ((element >= 'a') && (element <= 'z'))
      element +='A'-'a';
    return element;
  }
};

int main () 
{
  mycontainer<int> myint (7);
  mycontainer<char> mychar ('j');

  cout << myint.increase() << endl;
  cout << mychar.uppercase() << endl;
}
*/

/////////////////////////////////////////////////////////////////

/* non type parameters for templates -- a new example 

template <class T, int N> class mysequence {
  T memblock [N];
public:
  void setmember (int x, T value); // x is the index
  T getmember (int x); // again, x is the index
};

template <class T, int N> void mysequence<T,N>::setmember (int x, T value) {
  memblock[x]=value;
}

template <class T, int N> T mysequence<T,N>::getmember (int x) {
  return memblock[x];
}

int main () 
{
  mysequence <int,5> myints;
  mysequence <double,5> myfloats;

  myints.setmember (0,100);
  myfloats.setmember (3,3.1416);

  cout << myints.getmember(0) << '\n';
  cout << myfloats.getmember(3) << '\n';
}
*/

/////////////////////////////////////////////////////////////////

/* default type and non-type parameters

template <class T=int, int N=2> class mysequence {
  T memblock [N];
public:
  void setmember (int x, T value); // x is the index
  T getmember (int x); // again, x is the index
};

template <class T, int N> void mysequence<T,N>::setmember (int x, T value) {
  memblock[x]=value;
}

template <class T, int N> T mysequence<T,N>::getmember (int x) {
  return memblock[x];
}

int main () 
{
  mysequence <int,5> myints;
  mysequence <float,5> myfloats;
  mysequence <> myints2;

  myints.setmember(0, 100);
  myfloats.setmember(3, 3.1416);
  myints2.setmember(1, 25);

  cout << myints.getmember(0) << '\n';
  cout << myfloats.getmember(3) << '\n';
  cout << myints2.getmember(1) << '\n';
}
*/

/////////////////////////////////////////////////////////////////

/* mutiple templated types 

template <class T, class U> void squareAndPrint(T x, U y)
{
  T result;
  U otherVar;
  
  cout << "X: " << x << " " << x*x << endl;
  cout << "Y: " << y << " " << y*y << endl;
}

int main()
{
  int ii = 2;
  float jj = 2.1;

  squareAndPrint<int, float>(ii, jj);
}
*/
