// lab3.cpp : Defines the entry point for the console application.
//

#include "std_lib_facilities.h"

class badTemp{};

double ctok(double c)
{
	if (c < -273.15) throw badTemp();
	double k = c + 273.15;
	return k;
}

int main()
{
	try
	{
		while (cin)
		{
			double c = 0;
			cout << "please input the temperature in celsius that you want to convert to kelvin" << endl;
			cin >> c;
			cout << ctok(c) << endl;
		}
	}
	catch(badTemp)
	{
		cerr << "you input a temperature below absolute zero" << endl;
		return 1;
	}
	catch(...)
	{
		cerr << "something went wrong!" << endl;
		return 2;
	}
}

