// Zhongren Shao, shaoz
// assignment 7

#include "std_lib_facilities.h"
#include <limits.h>
#include "date.h"

//keeps track of the file names used in the program, thus these can be changed here provided the new file is in a suitable format
//	"udat" contains a list of all customers, their names, and their related account numbers. "t" contains the total number of accounts as well 
//	as the current date. size is a changeable variable that determines the total number of accounts that can be had at any one time, but if size
//	is changed the database has to be rebuilt, which i currently don't have a function for
string userData = "udat";
string all = "t";
date today;
int size = 10;

//gets the current date for calculating interest payments. the current date is stored in the "t" file, along with the total number of accounts
date getDate()
{
	ifstream ifs(all.c_str());
	string day;
	ifs >> day >> day;
	today = date(day);
	return today;
}

//increments the current date by 1 day
date incDate()
{
	ifstream ifs(all.c_str());
	string t, day;
	ifs >> t >> day;
	ifs.close();
	today = date(day);
	++today;
	ofstream ofs(all.c_str());
	ofs << t << " " << today;
	return today;
}

//note: I found a solution that didn't use most of the functions that i wrote in the accounts classes, I told Andrew about this when i went to 
//	see him during office hours Wednesday

//base class for accounts
class account
{
public:
	//getters
	string getUser() const { return user;} 
	date getDOB() const { return DOB;}
	virtual string getAcctID() const =0;
	virtual double getBal() const =0;
	virtual char getType() const =0;
protected:
	string user;
	date DOB;
};

//derived class for checking accounts
class checking : public account 
{
public:
	//constructor
	checking(const string u, const string no, const date dob, const double val)
		: type('c'), bal(val), acctID(no)
	{
	DOB = dob;
	user = u;
	}

	//getters
	string getAcctID() const { return acctID;}
	char getType() const { return type;}
	double getBal() const { return bal;}

	//adds the given value to the current balance
	void add(const double& val) { bal += val;}
	
	//subtracts the given value from the current balance
	void sub(const double& val) { bal -= val;}

	//updates the balance in the account file to the current balance in the object
	void updateBal()
	{
		string temp, copy;
		ifstream ifs(acctID.c_str());
		for (int i = 0; i < 9; ++i)
		{
			ifs >> temp;
			copy.append(temp);
			copy.append(" ");
		}
		ifs.ignore(INT_MAX, '\n');
		stringstream ss;
		ss << bal;
		ss >> temp;
		copy.append(temp);
		while (!ifs.eof())
		{
			copy.append("\n");
			getline(ifs, temp);
			copy.append(temp);
		}
		ifs.close();
		ofstream ofs(acctID.c_str());
		ofs << copy;
	}

	//records the transaction specified to the account's file
	void recTran(const char& t, const double& val, const string& reason)
	{
		ofstream ofs(acctID.c_str(), ios_base::app);
		if (t == 'c')
			ofs << "Credit " << today << " $" << val << " " << reason << endl;
		else if (t == 'd')
			ofs << "Debit " << today << " $" << val << " " << reason << endl;
	}
	
private:
	char type;
	double bal;
	string acctID;
};

//derived class for savings accounts
class saving : protected account
{
public:
	//constructor
	saving(string u, string no, date dob, double val)
		: type('s'), bal(val), acctID(no)
	{
	DOB = dob;
	user = u;
	}

	//getters
	string getAcctID() const { return acctID;}
	char getType() const { return type;}
	double getBal() const { return bal;}

	//adds the given value to the current balance
	void add(const double& val) { bal += val;}
	
	//subtracts the given value from the current balance
	void sub(const double& val) { bal -= val;}

	//updates the balance in the account file to the current balance in the object
	void updateBal()
	{
		string temp, copy;
		ifstream ifs(acctID.c_str());
		for (int i = 0; i < 9; ++i)
		{
			ifs >> temp;
			copy.append(temp);
			copy.append(" ");
		}
		ifs.ignore(INT_MAX, '\n');
		stringstream ss;
		ss << bal;
		ss >> temp;
		copy.append(temp);
		while (!ifs.eof())
		{
			copy.append("\n");
			getline(ifs, temp);
			copy.append(temp);
		}
		ifs.close();
		ofstream ofs(acctID.c_str());
		ofs << copy;
	}

	//records the transaction specified to the account's file
	void recTran(const char& t, const double& val, const string& reason)
	{
		ofstream ofs(acctID.c_str(), ios_base::app);
		if (t == 'c')
			ofs << "Credit " << today << " $" << val << " " << reason << endl;
		else if (t == 'd')
			ofs << "Debit " << today << " $" << val << " " << reason << endl;
	}

	//checks for minimum balance, and deducts $20 if the total balance goes below the required minimum balance
	void minChk()
	{
		if (bal < 500)
		{
			cout << "$20 has been deducted from your account because the total balance went below the required minimum of $500." << endl;
			bal = max(0.0, bal - 20);
			updateBal();
			recTran('d', 20.0, "below minimum balance");
		}
		return;
	}

	//checks for interest paid and pays interest if due, recording in the account file
	void intChk()
	{
		ifstream ifs(acctID.c_str());
		ifs.ignore(INT_MAX, '\n');
		int count = 0;
		while (!ifs.eof())
		{
			string last, buf, chk;
			ifs >> buf >> last >> buf >> chk;
			if (chk == "interest")
				count++;
			ifs.ignore(INT_MAX, '\n');
		}
		for (int i = daysTill(DOB, today)/365 - count; i > 0; --i)
		{
			string year;
			double due = bal * .05;
			bal += due;
			stringstream ss;
			ss << today.getYear() - i + 1;
			ss >> year;
			cout << "You have earned interest due of $" << due << " on your savings account for the year " << year << "." << endl;
			recTran('c', due, "interest for year " + year);
		}
		updateBal();
	}
private:
	char type;
	double bal;
	string acctID;
};

//declarations first, to make the code neater
void openAcct();
void transact();

//entry point into program, displays current date, and offers a choice of options
int main()
{
	getDate();
	cout << "Welcome, enter your choice below. The date today is " << today << "." << endl;
	loop:
	cout << "1. create a bank account \n2. carry out transaction \n3. advance to next day \n4. exit" << endl;
	int in;
	cin >> in;
	if (cin.fail() || cin.bad())
	{
		cerr << "You have entered invalid input, please try again." << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		goto loop;
	}

	switch(in)
	{
	case 1:
		openAcct();
		break;
	case 2:
		transact();
		break;
	case 3:
		today = incDate();
		cout << "Date updated! It is now " << today << "." << endl;
		goto loop;
	case 4:
		return 0;
	default:
		cerr << "You have entered invalid input, please try again." << endl;
		goto loop;
	}
	return 0;
}

//declarations first, to make the code neater
bool verify(const string, const string, const string, const string);
int nameTaken(const string&);
int inc();
void newAcct(const string&);
void newCust(const string&);

//entry point for opening a new account. offers choices after account is opened to do something else
void openAcct()
{
	string user;
	cout << "You have chosen to open an account. Enter 1 to return to the previous menu, or enter your desired username below:" << endl;
	do
	{
	loop:
		cout << "It should not be longer than " << size << " characters." << endl;
		cin >> user;
		if (user == "1")
		{
			main();
			return;
		}
		switch(nameTaken(user))
		{
		case 0:
			cout << "You can't choose that name. Please try again." << endl;
			user = string(size, '0');
			goto loop;
		case 1:
			newAcct(user);
			break;
		case 2:
			cout << "Sorry, the name you provided did not match the name of the account holder. Please enter the username again, or enter a new one." << endl;
			goto loop;
		case 3:
			newCust(user);
			break;
		default:
			return;
		}
	} while(user.length() > size);
	cout << "\nAccount successfully opened. Please select a choice from below: \n1. open another account \n2. perform a transaction \n3. return to main menu" << endl;
	
	loop2:
	cin >> user;
	if (user == "1")
		goto loop;
	else if (user == "2")
	{
		transact();
		return;
	}
	else if (user == "3")
	{
		main();
		return;
	}
	else
	{
		cerr << "Invalid input. Please try again." << endl;
		goto loop2;
	}
}

//checks if the first and last name given for a current account holder matches with the one in records
bool verify(const string first, const string last, const string f, const string l)
{
	return first == f && last == l;
}

//checks if a given user name is currently available, and tells if a given username is in the database. if so, also checks the account type 
//	currently held, and asks for verification of the customer's name to open a new account of the other kind
int nameTaken(const string& user)
{
  ifstream ifs(userData.c_str());
	while (!ifs.eof())
	{
		string chk;
		ifs >> chk;
		string accts;
		ifs >> accts;
		if (user == chk)
		{
			if (accts == "cs") return 0;
			cout << "It looks like this user already has a ";
			if (accts == "c")
				cout << "checking ";
			else
				cout << "savings ";
			cout << "account with us.\nPlease enter his/her first name followed by last to verify that this is the same customer." << endl;
			string first, last, f, l;
			cin >> first >> last;
			ifs.ignore(INT_MAX, '|');
			ifs.ignore(INT_MAX, '|');
			ifs >> f >> l;
			if (verify(first, last, f, l))
				return 1;
			else
				return 2;
			return 0;
		}
		ifs.ignore(INT_MAX, '\n');
	}
	return 3;
}

//increases the account counter in "t" when an account is added
int inc()
{
	ifstream tifs(all.c_str());
	int total;
	string input;
	tifs >> total >> input;
	if (tifs.fail())
		total = 0;
	tifs.close();
	ofstream fs(all.c_str());
	total++;
	fs << total << " " << date(input);
	return total;
}

//function to add new account for a new customer. updates user database and creates a new file to keep track of transactions and info 
//	for the new account, named with the account number
void newAcct(const char type, const string& user, const string& first, const string& last, date dob)
{
  ofstream ofs(userData.c_str(), ios_base::app);
	int total = inc();
	string ID;
	stringstream ss;
	ss << total;
	ss >> ID;
	ofstream acct(ID.c_str());
	ofs << setw(size) << user << ' ' << setw(2) << type << " | ";
	switch(type)
	{
	case 'c':
		{
			ofs << setw(size) << total << ' ' << setw(size) << 0;
			break;
		}
	case 's':
		{
			ofs << setw(size) << 0 << ' ' << setw(size) << total;
			break;
		}
	}
	ofs << " | " << first << ' ' << last << '\n';
	ofs.close();
	acct << "ID: " << ID << " Owner: " << user << " Type: " << type << " DOB: " << dob << " Bal: " << 0 << endl;	
}

//entry point for adding a new customer(ie one whose chosen username is not in the database). asks for input of the user info of the new customer
//	and prevents an account from being created beyond today's date
void newCust(const string& user)
{
	string first, last;
	cout << "Please enter the first name of the customer, followed by the last:" << endl;
	cin >> first >> last;
	char type = 'a';
	cout << "Please choose the type of account that you would like to set up:" << endl;
	loop:
	cout << "s for Savings, c for Checking" << endl;
	cin >> type;
	type = tolower(type);
	if (type != 99 && type != 115)
	{
		cerr << "You have entered invalid input, please try again." << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		goto loop;
	}
	cout << "Please enter the date the account was opened, in the format m/d/yyyy or using any other seperator in place of '/':" << endl;
	loop2:
	try
	{
		string input;
		cout << "Make sure the date is valid." << endl;
		cin >> input;
		date dob(input);
		if (daysTill(dob, today) < 0)
		{
			cerr << "Error! The date you supplied is in the future. Please try again." << endl;
			goto loop2;
		}
		newAcct(type, user, first, last, dob);
	}
	catch(badDate)
	{
		cout << "Please try again." << endl;
		cin.ignore(INT_MAX, '\n');
		cin.clear();
		goto loop2;
	}
}

//updates the user database, when an existing user creates another account of the other kind, and also creates the file associated with the new
//	account
void updateUdat(string* temp, const string& user, const date& dob)
{
	string chk;
	ifstream ifs(userData.c_str());
		ifs >> chk;
		while (chk != user)
		{
			ifs.seekg(-size, ios_base::cur);
			getline(ifs, chk);
			temp->append(chk);
			temp->append("\n");
			ifs >> chk;
		}
		ifs.seekg(-size, ios_base::cur);
		getline(ifs, chk);
		int acctID = inc();
		stringstream ss;
		ss << acctID;
		string ID;
		ss >> ID;
		ofstream acct(ID.c_str());
		for (int i = ID.length(); i < size; ++i)
			ID.insert(0, " ");
		char type = chk.at(size+2);
		switch(type)
		{
		case 'c':
			chk.replace(2*size+7, size, ID);
			type = 's';
			break;
		case 's':
			chk.replace(size+6, size, ID);
			type = 'c';
			break;
		}
		chk.replace(size+1, 2, "cs"); 
		temp->append(chk);
		char c = ifs.peek();
		if (c != 3)
			temp->append("\n");
		while (!ifs.eof())
		{
			getline(ifs, chk);
			chk.append("\n");
			temp->append(chk);
		}
		acct << "ID: " << ID << " Owner: " << user << " Type: " << type << " DOB: " << dob << " Bal: " << 0 << endl;
}

//entry point for adding an account of the other kind for an existing customer, asks for date opened of the account and prevents a future date
void newAcct(const string& user)
{
	string* temp = new string;
	string chk, input;
	cout << "Please enter the date the account was opened, in the format m/d/yyyy or using any other seperator in place of '/':" << endl;
	loop:
	try
	{
		cout << "Make sure the date is a valid one." << endl;
		cin >> input;
		date dob(input);
		if (daysTill(dob, today) < 0)
		{
			cerr << "Error! The date you supplied is in the future. Please try again." << endl;
			goto loop;
		}
		updateUdat(temp, user, dob);
		ofstream ofs(userData.c_str());
		ofs << *temp;
		delete temp;
		ofs.close();
	}
	catch(badDate)
	{
		cout << "Please try again." << endl;
		cin.ignore(INT_MAX, '\n');
		cin.clear();
		goto loop;
	}
}

//declarations first, to make the code neater
bool ifCust(const string&, const vector<string>);
bool ifAcct(const string&, const string&, char&);
void credAcct(const string&, const string&, const date&, const double&, const char&);
void debAcct(const string&, const string&, const date&, const double&, const char&);

//entry point for all transactions. offers options for various transactions 
void transact()
{
	vector<string> users;
	ifstream ifs(userData.c_str());
	string user, ID;
	char type;
	while (!ifs.eof())
	{
		ifs >> user;
		users.push_back(user);
		ifs.ignore(INT_MAX, '\n');
	}
	ifs.close();
	users.pop_back();
	loop:
	do 
	{
		cout << "Please input the customer's username." << endl;
		cin >> user;
		if (!ifCust(user, users))
			cout << "Sorry, no customer with that username was found. Please try again." << endl;
	} while (!ifCust(user, users));
	cout << "Please input " << user << "'s account number." << endl;
	cin >> ID;
	if (!ifAcct(ID, user, type))
	{
		cout << "Sorry, the account number you provided did not match with the username. Please try again." << endl;
		goto loop;
	}
	loop2:
	cout << "This is " << user << "'s ";
	switch(type)
	{
	case 'c':
		cout << "checking ";
		break;
	case 's':
		cout << "savings ";
		break;
	}
	cout << "account. Please select an option from below: \n1. check balance \n2. make deposit to account \n3. make withdrawal from account" << endl;
	int opt;
	cin >> opt;
	if (cin.fail() || cin.bad())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		goto loop2;
	}
	ifs.open(ID.c_str());
	string buf, input;
	double bal;
	ifs >> buf >> buf >> buf >> buf >> buf >> buf >> buf >> input >> buf >> bal;
	switch(opt)
	{
	case 1:
		cout << "The current balance in this account is $" << setprecision(2) << fixed << bal << "." << endl;
		break;
	case 2:
		credAcct(user, ID, date(input), bal, type);
		break;
	case 3:
		debAcct(user, ID, date(input), bal, type);
		break;
	default:
		cerr << "You have entered invalid input, please try again." << endl;
		ifs.close();
		goto loop2;
	}
	ifs.close();
	loop3:
	cout << "\nTransaction complete! Please select an option from below: \n1. perform another transaction on another account \n2. perform another transaction on this account \n3. open a new account \n4. return to main menu" << endl;
	cin >> opt;
	if (cin.fail() || cin.bad())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		goto loop3;
	}
	switch(opt)
	{
	case 1:
		goto loop;
	case 2:
		goto loop2;
	case 3:
		openAcct();
		return;
	case 4:
		main();
		return;
	default:
		cerr << "You have entered invalid input, please try again." << endl;
		goto loop3;
	}
}

//checks if a supplied username is that of an existing customer in the database
bool ifCust(const string& user, const vector<string> users)
{
	for (int i = 0; i < users.size(); ++i)
		if (users[i] == user)
			return true;
	return false;
}

//checks if a supplied account number matches with the supplied username in the database
bool ifAcct(const string& ID, const string& user, char& type)
{
	ifstream ifs(ID.c_str());
	string chk, buf;
	ifs >> buf >> buf >> buf >> chk >> buf >> type;
	return chk == user;
}

//entry point for credit transactions(deposits). takes the amount to be deposited, and offers options after the deposit is successful
void credAcct(const string& user, const string& ID, const date& dob, const double& bal, const char& t)
{
	double val;
	loop:
	cout << "Please input the amount of money that you would like to deposit: " << endl;
	cin >> val;
	if (cin.fail() || cin.bad())
	{
		cerr << "You have entered invalid input, please try again." << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		goto loop;
	}
	else if (val < 0)
	{
		cout << "Sorry, you cannot enter a negative number. Please try again." << endl;
		goto loop;
	}
	if (t == 'c')
	{
		checking* acct = new checking(user, ID, dob, bal);
		acct->add(val);
		acct->updateBal();
		acct->recTran('c', val, "deposit");
		cout << "The new balance in the account is $" << acct->getBal() << "." << endl;
	}
	else if (t == 's')
	{
		saving* acct = new saving(user, ID, dob, bal);
		acct->intChk();
		acct->add(val);
		acct->recTran('c', val, "deposit");
		acct->updateBal();
		cout << "The new balance in the account is $" << acct->getBal() << "." << endl;
	}
}

//entry point for debit transactions(withdrawals). takes the amount to be withdrew, and offers options after the withdrawal is successful
void debAcct(const string& user, const string& ID, const date& dob, const double& bal, const char& t)
{
	double val;
	loop:
	cout << "Please input the amount of money that you would like to withdraw: " << endl;
	cin >> val;
	if (cin.fail() || cin.bad())
	{
		cerr << "You have entered invalid input, please try again." << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		goto loop;
	}
	else if (val < 0)
	{
		cout << "Sorry, you cannot enter a negative number. Please try again." << endl;
		goto loop;
	}
	else if (val > bal)
	{
		cout << "Sorry, insufficient funds. You only have $" << fixed << setprecision(2) << bal << " in this account. Please try again." << endl;
		goto loop;
	}
	if (t == 'c')
	{
		checking* acct = new checking(user, ID, dob, bal);
		acct->sub(val);
		acct->updateBal();
		acct->recTran('d', val, "withdrawal");
		cout << "The new balance in the account is $" << fixed << setprecision(2) << acct->getBal() << "." << endl;
	}
	else if (t == 's')
	{
		saving* acct = new saving(user, ID, dob, bal);
		acct->sub(val);
		acct->recTran('d', val, "withdrawal");
		acct->updateBal();
		acct->minChk();
		acct->intChk();
		cout << "The new balance in the account is $" << fixed << setprecision(2) << acct->getBal() << "." << endl;
	}
}
