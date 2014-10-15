// lab2.cpp : Defines the entry point for the console application.
//

#include "std_lib_facilities.h"

void intAndChar();
void currCon();
void example();

int main()
{
	char func;
	cout << "Please enter a, b, or c, corresponding to the exercises in order:" << endl;
	cin >> func;
	switch(func)
	{
	case 'a':
		currCon();
		break;
	case 'b':
		intAndChar();
		break;
		currCon();
		break;
	case 'c':
		example();
		break;
	default:
		break;
	}
}

void intAndChar()
{
	for (int i = 0; i < 256; ++i)
	{
		char x = i;
		cout << i << '\t' << x << endl;
	}

	cout << "uppercase and digits:" << endl;

	for (int i = 0; i < 256; ++i)
	{
		char c = i;
		if (c >= 'A' && c <= 'Z')
			cout << i << '\t' << c << endl;
		if (c >= '0' && c <= '9')
			cout << i << '\t' << c << endl; 
	}

	main();
}

void currCon()
{
	double val;
	double conver;
	char curr;
	cout << "Please enter a dollar value, followed by a space, followed by one of the following letters, representing the corresponding currencies to convert it to US dollars:" << endl
		<< "y\tyen" << endl
		<< "e\teuros" << endl
		<< "p\tpounds" << endl
		<< "c\tyuan" << endl
		<< "k\tkroner" << endl;
	cin >> val >> curr;
	cout << val;
	switch (curr)
	{
	case 'y':
		conver = val * 0.01112;
		cout << " yen";
		break;
	case 'e':
		conver = val * 1.330139;
		cout << " euros";
		break;
	case 'p':
		conver = val * 1.58806;
		cout << " pounds";
		break;
	case 'c':
		conver = val * 0.1609;
		cout << " yuan";
		break;
	case 'k':
		conver = val * 0.18;
		cout << " kroner";
		break;
	default:
		cout << "That is not a valid input." << endl;
		break;
	}
	cout << " is equal to " << conver << " dollars." << endl;
	main();
}

void example()
{
	vector<string> words;
	string temp;
	while (cin >> temp)
		words.push_back(temp);
	cout << "Number of words: " << words.size() << endl;

	sort(words.begin(), words.end());

	for (int i = 0; i < words.size(); ++i)
		if (i == 0 || words[i-1] != words[i])
			cout << words[i] << endl;

	main();
}