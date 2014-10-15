#include<iostream>
using namespace std;

// sums the values from 0...n
int summation(int summation)
{
  int sum = 0;
  // stop when i <= summation
  for (int i = 0; i = summation; i++)
    {
      sum += i;
    }

  return sum;
}

int main()
{
  int summed = summation(10);
  cout << "summed is: " << summed;
}


