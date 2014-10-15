//Zhongren Shao
//assignment 5

#include "std_lib_facilities.h"

//class for catching bad input
class badDate{};

//key for determining day of the week
int monthKey[12] = {5, 1, 1, 4, 6, 2, 4, 0, 3, 5, 1, 3};

//checks if given year is a leap year
//good for checking any year you can think of
bool isLeap(int y)
{
	if (y % 400 == 0) 
		return true;
	else if (y % 100 == 0)
		return false;
	else if (y % 4 == 0) 
		return true;
	else
		return false;
}

//returns the number of days in a given month
//better as a general function, though I originally implemented it inside the class with no parameters, but that was rather limiting
int daysInMonth(int m, int y)
{
	int monthDays = 31;
	switch(m)
	{
	case 2:
		monthDays = (isLeap(y))?29:28;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		monthDays = 30;
		break;
	}
	return monthDays;
}

//returns the number of days in a given year
int numDays(int y)
{
	if (isLeap(y))
		return 366;
	else return 365;
}

//every method in the date class is an operation that can be performed on a date, and which are likely to be commonly used. the rest go outside the class
class date
{
private:
	int day;
	int month;
	int year;

	//converts string input into an integer
	int strToInt(string number)
	{	
		return atoi(number.c_str());
	}

	//parses and checks string input
	void parseChk(string input)
	{
		if (isDate(strToInt(input.substr(3, 2)), strToInt(input.substr(0, 2)), strToInt(input.substr(6, input.length() - 6))))
		{
			day = strToInt(input.substr(3, 2));
			month = strToInt(input.substr(0, 2));
			year = strToInt(input.substr(6, input.length() - 6));
		}
		else 
			throw badDate();
	}

	//checks if a given date is a valid date
	bool isDate(int d, int m, int y)
	{
		if (y < 1950 || y > 2015)
		{
			cout << "Error! Unsupported year." << endl;
			return false;
		}

		if (m < 1 || m > 12) 
		{
			cout << "Error! Invalid month." << endl;
			return false;
		}

		int maxDays = daysInMonth(m, y);

		if (d <= 0 || d > maxDays) 
		{
			cout << "Error! Invalid day of the month." << endl;
			return false;
		}
		return true;
	}

public:

	//constructors
	date() {}

	date(string Date) {
		parseChk(Date);}

	date(int d, int m, int y)
	{
		if (isDate(d, m, y))
		{
			day = d;
			month = m;
			year = y;
		}
		else 
			throw badDate();
	}

	//getters
	int getDay() const
	{
		return day;
	}

	int getMonth() const
	{
		return month;
	}

	int getYear() const
	{
		return year;
	}

	//increment operator
	void operator++()
	{
		if (day < daysInMonth(month, year))
			day += 1;
		else if(month == 12)
		{
			day = 1;
			month = 1;
			year += 1;
		}
		else
		{
			day = 1;
			month += 1;
		}
	}

	//calculates day of the week based on the date
	int dayOfWeek() const
	{
		int val = day;
		val += monthKey[month - 1];
		val += year % 100;
		val += (year % 100) / 4;
		val -= 2 * ((year / 100) % 4);
		if (isLeap(year) && month <= 2)
			val -= 1;
		return (val % 7) + 1;
	}
};

//equality checker overload
//could have implemented this in the class, but that caused confusion since it didn't match up with the normal usage of the == operator
bool operator==(date& a, date& b)
{
	return a.getDay() == b.getDay() &&
		a.getMonth() == b.getMonth() &&
		a.getYear() == b.getYear();
}

//non equality checker overload
//outside for same reason as above
bool operator!=(date& a, date& b)
{
	return !(a == b);
}

//cout operator overload
ostream& operator<<(ostream& os, date d)
{
	return os << d.getMonth() 
		<< "/" << d.getDay()
		<< "/" << d.getYear();
}

//takes 2 dates and returns the number of days from the first to the second
int daysTill(date a, date b)
{
	int count = 0;
	date x = a;
	date y = b;
	while (a != y && b != x)
	{
		++a;
		++b;
		count++;
	}
	if (a == y)
		return count;
	else
		return -count;
}

//returns the date of the end of the semester given the date of the start of the semester
date endOfSem(date start)
{
	int days = 105;
	while (days > 0)
	{
		++start;
		--days;
	}
	return start;
}

//returns the date on which thanksgiving falls given the date of the first of november in any year
date thanksgiving(date d)
{
	int gap = 21;
	while (d.dayOfWeek() != 4)
		++d;
	while (gap > 0)
	{
		++d;
		--gap;
	}
	return d;
}

//sorry i had to use goto here, but i really couldn't think of a way to make the program break out of the catch block once it had gone in
int main()
{
	start:
	try 
	{
		cout << "Please enter a date below, in the format mm/dd/yyyy or using any other seperator in place of '/':" << endl;
		string input;
		cin >> input;
		date val(input);

		//values for use in the operations
		date copy = val;
		date other;
		cout << "The date you have chosen is " << val << '.' << endl;

		//loop
		while (cin)
		{
			cout << endl
				<< "Please enter the corresponding number of the function that you would like to perform:" << endl
				<< "1. Is this year a leap year?" << endl
				<< "2. What are the number of days in this year?" << endl
				<< "3. What are the number of days till another date?" << endl
				<< "4. What date is Thanksgiving on this year?" << endl
				<< "5. If this date is the start of the semester, when will it end?" << endl
				<< "6. What's tomorrow's date?" << endl
				<< "7. Enter a new date." << endl
				<< "8. Quit" << endl;
			int choice;
			cin >> choice;
			switch(choice)
			{
			case 1:
				if (isLeap(val.getYear()))
					cout << "Yes, " << val.getYear() << " is a leap year." << endl;
				else
					cout << "No, " << val.getYear() << " is not a leap year." << endl;
				break;
			case 2:
				cout << "The number of days in the year " << val.getYear() << " is " << numDays(val.getYear()) << '.' << endl;
				break;
			case 3:
				cout << "Please enter the date that you would like to calculate the days till: ";
				cin >> input;
				other = date(input);
				cout << "There is/are " << daysTill(val, other) << " day(s) till " << other << '.' << endl;
				break;
			case 4:
				cout << "Thanksgiving is on " << thanksgiving(date(1,11,val.getYear())) << " this year." << endl;
				break;
			case 5:
				cout << "The semester will end on " << endOfSem(val) << '.' << endl;
				break;
			case 6:				
				++copy;
				cout << "The date tomorrow is " << copy << endl;
				break;
			case 7:
				goto start;
				break;
			case 8:
				cout << "Goodbye!" << endl;
				goto end;
				break;
			}
		}
	}
	catch(badDate)
	{
		cout << "You have entered an invalid date. Please start again." << endl;
		goto start;
	}
end:
	return 0;
}