//Zhongren Shao, shaoz
//assignment 3

#include "std_lib_facilities.h"

void input(vector<int> aov[]);
void printer(vector<int> aov[]);
int dayCheck(string day);

const int a = 8;

int main()
{
	vector<int> aov[a];
	input(aov);
	printer(aov);

	return 0;
}

//handles input, checks the day and pushes the values onto the vector
void input(vector<int> aov[])
{
	string day;
	int val;
	cout << "Please input day-value pairs, with the value following the day.\nTo end entry, enter 'q q':" << endl;
	while (day != "q")
	{
		if (cin >> day >> val)
			aov[dayCheck(day)].push_back(val);
		else
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}
}

// handles output, takes the array of vectors and prints out all the values
void printer(vector<int> aov[])
{
	for (int i = 0; i < a-1; ++i)
	{
		string day;
		int sum = 0;

		switch(i)
		{
		case 0:
			day = "Monday";
			break;
		case 1:
			day = "Tuesday";
			break;
		case 2:
			day = "Wednesday";
			break;
		case 3:
			day = "Thursday";
			break;
		case 4:
			day = "Friday";
			break;
		case 5:
			day = "Saturday";
			break;
		case 6:
			day = "Sunday";
			break;
		}
		cout << day << " values:" << endl;

		for (int x = 0; x < aov[i].size(); ++x)
		{
			cout << aov[i][x] << " ";
			sum += aov[i][x];
		}

		cout << "\nSum of " << day << " values:" << sum << endl << endl;
	}

	cout << "Number of rejected values: " << aov[7].size() << endl;
}

//checks if the day string input is valid, and if so, which day it corresponds to, returning the respecttive index in the array
int dayCheck(string day)
{
	if (day == "Monday" || day == "monday" || day == "Mon" || day == "mon")
		return 0;
	else if (day == "Tuesday" || day == "tuesday" || day == "Tue" || day == "tue")
		return 1;
	else if (day == "Wednesday" || day == "wednesday" || day == "Wed" || day == "wed")
		return 2;
	else if (day == "Thursday" || day == "thursday" || day == "Thu" || day == "thu")
		return 3;
	else if (day == "Friday" || day == "friday" || day == "Fri" || day == "fri")
		return 4;
	else if (day == "Saturday" || day == "saturday" || day == "Sat" || day == "sat")
		return 5;
	else if (day == "Sunday" || day == "sunday" || day == "Sun" || day == "sun")
		return 6;
	else 
		return 7;
}


