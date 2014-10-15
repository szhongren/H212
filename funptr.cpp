#include <iostream>
using namespace std;

int main ()
{
  // declare function prototypes
  void map (double*, int, double (*)(double));
  // last arg: return type of function, * = ptr to function, double = arg type of func
  double increment (double);
  double print (double);

  double A[] = {1, 2, 3, 4, 5};
  int i;
  cout << "Original A: ";
  for (i=0; i < 5; i++)
    cout << " " << A[i];
  cout << endl;

  map(A, 5, increment);
  
  cout << "Mapped A: ";
  // for (int i=0; i < 5; i++)
  //  cout << " " << A[i];
  map(A, 5, print);
  cout << endl;
}


double increment (double a)
{
  return a + 1;
}

double print (double a)
{
  cout << " " << a;
  return a;
}

void map (double *A, int len, double (*operation)(double))
{
  for (int i=0; i < len; i++)
    A[i] = (*operation)(A[i]);
}

