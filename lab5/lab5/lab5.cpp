// lab5.cpp : Defines the entry point for the console application.
//

#include "std_lib_facilities.h"

class ISBN
{
private:
	string num;

	bool isValid(int num, char let)
	{
		if (num <= 9999999999 || num >= 1000000000)
			if ((let >= 48 && let <= 57) || (let >= 65 && let <=90))
				return true;
		return false;
	}

public:
	ISBN()
	{
	}

	ISBN(string input)
	{
		if (validInput(input))
			num = input;
	}

	ISBN(int input, char inletter)
	{
		if (isValid(input, inletter))
		{
			stringstream out;
			out << input;
			num = out.str() + inletter;
			num.insert(1, "-");
			num.insert(5, "-");
			num.insert(9, "-");
			num.insert(11, "-");
		}
		else
		{
			cout << "Invalid ISBN number detected." << endl;
		}

	}

	bool validInput(string in)
	{
		if (in.substr(11, 1) == "-" && in.length() == 13)
		{
			int count;
			for (int i = 0; i < 12; ++i)
			{
				if (in.substr(i, 1) == "-")
					count++;
			}
			if (count == 3)
				return true;
		}
		return false;
	}

	string getISBN()
	{
		return num;
	}
};

class date
{
private:
	string date;
public:
	string getDate()
	{
		return date;
	}
};

class Book
{
private:
	string title;
	string author;
	date copyright;
	ISBN isbn;
	bool isIn;
public:
	Book(string authorLast, string authorFirst, string titl, date copy, ISBN isbnNo)
	{
		title = titl;
		author = authorFirst + authorLast;
		isbn = isbnNo;
		copyright = copy;
	}

	bool isCheckedIn()
	{
		return isIn;
	}

	string getISBN()
	{
		return isbn.getISBN();
	}

	string getAuthor()
	{
		return author;
	}
	
	string getCopyright()
	{
		return copyright.getDate;
	}

	string getTitle()
	{
		return title;
	}

	void setAuthor(string name)
	{
		author = name;
	}

	void setDate(date copy)
	{
		copyright = copy;
	}

	void setTitle(string titl)
	{
		title = titl;
	}

	void setISBN(ISBN num)
	{
		isbn = num;
	}

	void checkOut()
	{
		if (isIn)
		{
			isIn = false;
			cout << "Successful check out." << endl;
		}
		else
			cout << "Book is already checked out." << endl;
	}

	void checkIn()
	{
		if (!isIn)
		{
			isIn = true;
			cout << "Successful check in." << endl;
		}
		else 
			cout << "Book is already checked in." << endl;
	}
};

int main()
{
	return 0;
}

