// lab6.cpp : Defines the entry point for the console application.
//

#include "std_lib_facilities.h"

class coffee
{
private:
	string name;
	string prodRegion;
	double costOfLb;
	bool isDarkRoast;
public:
	coffee()
	{
		name = "Generic coffee";
		prodRegion = "Some place";
		costOfLb = 1.50;
		isDarkRoast = false;
	}
	coffee(string newName, double price)
	{
		name = newName;
		prodRegion = "Some place";
		costOfLb = price;
		isDarkRoast = false;
	}
	coffee(string newName, string region, double price, bool isDark)
	{
		name = newName;
		prodRegion = region;
		costOfLb = price;
		isDarkRoast = isDark;
	}
	string getName()
	{
		return name;
	}
	string getRegion()
	{
		return prodRegion;
	}
	double getPrice()
	{
		return costOfLb;
	}
	bool ifDark()
	{
		return isDarkRoast;
	}
	void updatePrice(double newPrice)
	{
		costOfLb = newPrice;
	}
	void getInfo()
	{
		cout << "Name: " << name << endl
			<< "Production region: " << prodRegion << endl
			<< "Price per pound: " << costOfLb << endl
			<< "Dark roast?: " << isDarkRoast << endl;
	}
	void priceWithTax()
	{
		cout << "Price per pound with tax: " << costOfLb * 1.08 << endl;
	}
};

int main()
{
	coffee test;
	test.getInfo();
	return 0;
}

