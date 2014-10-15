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
	void parseChk(string& input)
	{
		string d, m, y;
		int j = 0;
		for (int i = 0; i < input.length(); ++i)
		{
			char temp = input[i];
			if(!isdigit(temp))
			{
				++j;
				continue;
			}
			stringstream ss;
			ss << temp;
			string c;
			ss >> c;
			switch(j)
			{
			case 0:
				m.append(c);
				break;
			case 1:
				d.append(c);
				break;
			case 2:
				y.append(c);
				break;
			}
		}

		int dd, mm, yy;
		dd = strToInt(d);
		mm = strToInt(m);
		yy = strToInt(y);
		if (isDate(dd, mm, yy))
		{
			day = dd;
			month = mm;
			year = yy;
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

	date(string& Date) {
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