//assignment 1, pg 86 exercise 11

#include "std_lib_facilities.h"
#define size 6

//function prototypes
void asker(int vals[]);
void printer(int vals[]);
double adder(int vals[]);

int main()
{
	int counts[size];

	asker(counts);
	printer(counts);

	return 0;
}

//asks the user for the number of each coin that he has
void asker(int vals[size])
{
	int i = 0;
	while (i < size)
	{
		cout << "How many ";
		switch(i)
		{
		case 0:
			cout << "pennies";
			break;
		case 1:
			cout << "nickels";
			break;
		case 2:
			cout << "dimes";
			break;
		case 3:
			cout << "quarters";
			break;
		case 4:
			cout << "half dollars";
			break;
		case 5:
			cout << "dollars";
			break;
		}
		cout << " do you have?" << endl;
		cin >> vals[i];
		i++;
	}
}

//prints everything after all the number of coins have been input
void printer(int vals[size])
{
	int i = 0;
	double value = adder(vals);

	while (i < size)
	{
		cout << "You have " << vals[i] << " ";
		switch(i)
		{
		case 0: 
			cout << "penny";
			break;
		case 1:
			cout << "nickel";
			break;
		case 2:
			cout << "dime";
			break;
		case 3:
			cout << "quarter";
			break;
		case 4:
			cout << "half dollar";
			break;
		case 5:
			cout << "dollar";
			break;
		}

		if (vals[i] != 1)
			{
				if (i == 0)
					cout << "\bie";
				cout << "s";
			}
		cout << "." << endl;

		i++;
	}
	cout << "The value of all of your coins is $" << value << "." << endl;
}

//finds the total value of all the coins and returns it as a double in dollars
double adder(int vals[size])
{
	double total = 0;
	int i = 0;

	while (i < size)
	{
		switch(i)
		{
		case 0:
			total += vals[i];
			break;
		case 1:
			total += 5 * vals[i];
			break;
		case 2:
			total += 10 * vals[i];
			break;
		case 3:
			total += 25 * vals[i];
			break;
		case 4:
			total += 50 * vals[i];
			break;
		case 5:
			total += 100 * vals[i];
			break;
		}
		i++;
	}
	return total/100;
}