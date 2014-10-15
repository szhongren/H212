#include <iostream>

using namespace std;

// this is a test for gdb that contains no bugs!
int main()
{
  int i = 0;
  int j = 10;
  int temp = 0;

  for (int z = 0; z < 10; z++)
    {
      i++;
      j--;
      temp = i + j;
    }

  cout << "The value of i should be 10, and it is " << i << endl;
  cout << "The value of j should be 0, and it is " << j << endl;
  cout << "The value of temp should be 10, and it is " << temp << endl;

}