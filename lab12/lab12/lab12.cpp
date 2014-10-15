// lab12.cpp : Defines the entry point for the console application.
//

#include "../../std_lib_facilities.h"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void output(int i)
{
	cout << i << " ";
}

bool isOdd (int i) { return ((i%2)==1); }

int main() {
  // create our v1 and v2 vectors
  int i[] = { 2, 1, 5, 3, 4};
  vector<int> v(i, i + sizeof(i) / sizeof(int));
  int j[] = { 101, 913, 123, 4 };
  vector<int> v2(j, j + sizeof(j) / sizeof(int));;
  cout << "v: ";
  for_each(v.begin(), v.end(), output);
  cout << "v2: ";
  for_each(v2.begin(), v2.end(), output);
  cout << endl;

  vector<int> v3(9);
  sort(v.begin(), v.end());
  sort(v2.begin(), v2.end());
  merge(v.begin(), v.end(), v2.begin(), v2.end(), v3.begin());
  cout << "v3: ";
  for_each(v3.begin(), v3.end(), output);
  cout << endl;

  cout << "number of 4's: " << count(v3.begin(), v3.end(), 4) << endl;

  vector<int>::iterator found = find(v3.begin(), v3.end(), 4);
  v3.erase(found);

  int oddCount = count_if(v3.begin(), v3.end(), isOdd);
  cout << "odd: " << oddCount << " even: " << v3.size() - oddCount << endl;

  replace(v3.begin(), v3.end(), 913, 10);
  sort(v3.begin(), v3.end());
  cout << "sorted v3: ";
  for_each(v3.begin(), v3.end(), output);
  cout << endl;

  reverse(v3.begin(), v3.end());
  cout << "reversed v3: ";
  for_each(v3.begin(), v3.end(), output);
  cout << endl;
}

