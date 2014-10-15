//Zhongren Shao
//assignment 2

#include "std_lib_facilities.h"

bool ifPrime(int, vector<int>);
void printer(vector<int>);

int main()
{
	const int limit = 100;
	vector<int> primes(1);
	primes[0] = 2;

	for (int test = 3; test <= limit; test+=2)
	{
		if (ifPrime(test, primes))
			primes.push_back(test);
	}

	printer(primes);

	return 0;
}

//checks if a number is a prime using a growing vector of primes
bool ifPrime(int test, vector<int> primes)
{
	for (int i = 0; i < primes.size(); ++i)
	{
		if (test % primes[i] == 0)
			return false;
	}
	return true;
}

void printer(vector<int> primes)
{
	for (int i = 0; i < primes.size(); ++i)
	{
		cout << primes[i] << endl;
	}
}
