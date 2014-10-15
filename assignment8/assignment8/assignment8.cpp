// assignment8.cpp : Defines the entry point for the console application.
//

#include "std_lib_facilities.h"

#include "date.h"
#include "limits.h"

//date to keep track of his clothes usage and idmax to keep the names of the pairs unique
date dd(29, 3, 2013);
int idMax = 8;

//set class, for each set of clothes that he has
class set
{
public:
	//constructor
	set(int name)
		: id(name), uses(0) {}
	//getters
	int getID() { return id;}
	int getUses() { return uses;}
	//setter
	void setUses(int i) { uses = i;}
	//increases the use count of the set by 1
	void wear() { uses++;}
private:
	int id;
	int uses;
};

#include "linkedList.h"

//takes a string and checks if it is a number
bool isNum(string test)
{
	for (int i = 0; i < test.length(); ++i)
		if (!isdigit((char)test[i]))
			return false;
	return true;
}

//moves the clothes from the dirty pile to the clean pile, whether they are being laundered or reused
void move(LinkedList<set>* clean, LinkedList<set>* dirty, bool ifWash)
{
	if (ifWash)
	{
		Node<set>* washed =0;
		while (dirty->getSize() > 0)
		{
			washed = dirty->randPick();
			washed->getData()->setUses(0);
			clean->insertEnd(dirty->extract(washed));
		}
		cout << "Laundry done!" << endl;
	}
	else
	{
		cout << "Aker has reused his dirty clothes. He may reuse them for another " << 2 - dirty->getLast()->getData()->getUses() << " times before he has to wash them." << endl;
		while (dirty->getSize() > 0)
		{
			dirty->getFirst()->getData()->wear();
			clean->insertBeginning(dirty->pop_front());
		}
	}

	cout << "Buy new clothes? Enter the number of clothes to buy if yes, or n if no." << endl;
	string input;
	cin >> input;
	if (isNum(input))
	{
		int sets = atoi(input.c_str());
		for (sets; sets > 0; sets--)
		{
			clean->insertAfter(new Node<set>(idMax), clean->randPick());
			idMax++;
		}
	}
	cout << "Did Aker find a hole in the pair for today? (y/n)" << endl;
	cin >> input;
	Node<set>* today = clean->pop_back();
	if (input == "y" || input == "Y")
	{
		cout << "Aker has thrown away shirt number " << today->getData()->getID() << "." << endl;
		delete today;
	}
	else
		clean->insertEnd(today);
}

//loop function for handling logic and using each day's clothes
void next(LinkedList<set>* clean, LinkedList<set>* dirty)
{
	
	if (clean->getSize() == 0)
	{
		if (dirty->getLast()->getData()->getUses() == 3)
		{
			cout << "Aker cannot reuse these clothes any more. He will launder them." << endl;
			move(clean, dirty, true);
		}
		else
		{
			cout << "Aker has run out of clothes. Launder or repeat? (l/r)" << endl;
			char input;
			cin >> input;
			switch(input)
			{
			case 'l':
			case 'L':
				move(clean, dirty, true);
				break;
			case 'r':
			case 'R':
				move(clean, dirty, false);
				break;
			}
		}
		return;
	}
	else if (dirty->getSize() > 6)
	{
		cout << "Aker has used " << dirty->getSize() << " pairs of clothes. He has " << clean->getSize() << " pairs of clean clothes left. Launder or not? (y/n)" << endl;
		char input;
		cin >> input;
		switch(input)
		{
		case 'y':
		case 'Y':
			move(clean, dirty, true);
			return;
		case 'n':
		case 'N':
			break;
		}
	}
	dirty->insertEnd(clean->pop_back());
	++dd;
	return;
}

//end function for the whole program, outputs the list of clothes in each pile
void end(LinkedList<set>* clean, LinkedList<set>* dirty)
{
	cout << "Program ended. Here is the list of clean and dirty clothes." << endl;
	cout << "Clean clothes:" << endl;
	clean->out();
	cout << "Dirty clothes:" << endl;
	dirty->out();
}

//entry point, takes input for the initial loop
int main()
{
	LinkedList<set>* clean = new LinkedList<set>;
	LinkedList<set>* dirty = new LinkedList<set>;
	for (int i = 0; i < 8; ++i)
		clean->insertEnd(new Node<set>(i));
	char input;
	loop:
	cout << "Today's date is " << dd << " and Aker has " << clean->getSize() << " pairs of clean clothes and " << dirty->getSize() << " pairs of dirty clothes left." << endl;
	cout << "Do you want to continue? (y/n)" << endl;
	cin >> input;
	switch(input)
	{
	case 'y':
	case 'Y':
		next(clean, dirty);
		goto loop;
	case 'n':
	case 'N':
		end(clean, dirty);
		return 0;
	default:
		cout << "Sorry, unrecognized command." << endl << endl;
		goto loop;
	}
}

