#include "std_lib_facilities.h"
#include <typeinfo>

// ------------------------------------------------------------------------
/* dynamic_cast */

class CBase { virtual void dummy() {} };
class CDerived: public CBase { int a; };

int main () {
  try {
    CBase * pba = new CDerived;
    CBase * pbb = new CBase;
    CDerived * pd;
    
    pd = dynamic_cast<CDerived*>(pba);
    if (pd==0) cout << "Null pointer on first type-cast" << endl;
    
    pd = dynamic_cast<CDerived*>(pbb);
    if (pd==0) cout << "Null pointer on second type-cast" << endl;
    
  } catch (exception& e) {cout << "Exception: " << e.what();}
  return 0;
}
*/

// ------------------------------------------------------------------------
/* static_cast 

int main()
{
  int a = 31;
  int b = 3;
  float x = a/b;
  float y = static_cast<float>(a)/b;
  cout << "Output without static_cast = " << x << endl;
  cout << "Output with static_cast = " << y << endl;
  // Output without static_cast = 10
  // Output with static_cast = 10.3333
}  
*/

// ------------------------------------------------------------------------
/* reinterpret_cast

int main()
{
  // the reinterpret_cast operator is used convert a integer pointer
  // to a pointer of type "void" then converted into a integer
  // pointer.
  int *ptr = new int(20);
  cout << "First value = " << *ptr << endl;
  void *ptr2 = reinterpret_cast<void *>(ptr);
  int *ptr3 = reinterpret_cast<int *>(ptr2);
  cout << "Final reinterpret cast value is::" << *ptr3 << endl;
  // First value = 20
  // Final reinterpret cast value is:: 20

  // typecast from an integer (memory address -- one better know what they are doing!) to a character pointer:
  // attempting to print ptr_my or what it is pointing to will segfault
  // char *ptr_my = reinterpret_cast<char *>(0xb0000);
  // cout << "Pointer value: " << *ptr_my << endl;
  
  // if we use reinterpret_cast on a null-pointer, we get a null-pointer of the asked type
  char *ptr_my_second = 0;
  int *ptr_my_third = reinterpret_cast<int *>(ptr_my_second);
  if (ptr_my_third == NULL) cout << "We got null\n";
}
*/

// ------------------------------------------------------------------------
 /* const_cast

void example(const float &a)
{
  float &b = const_cast<float &> (a);
  b = 20.0;
}

int main()
{
  float c = 17.5;
  cout << "The value before const_cast is:: " << c << endl;
  example(c);
  cout << "The value after const_cast is::" << c << endl;
  return 0;
}
 */

// ------------------------------------------------------------------------
/* typeid

int main()
{
  int *a, b;
  char *c;
  // need to include "typeinfo" up at the top
  cout << "The type of a is: " << typeid(a).name() << endl;
  cout << "The type of b is: " << typeid(b).name() << endl;
  cout << "The type of c is: " << typeid(c).name() << endl;
}
*/
