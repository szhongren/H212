//Zhongren Shao, shaoz
//assignment 6

#include "std_lib_facilities.h"

//classes for error checking and eof checking, i didn't really understand how to use the standard eof checks in C++, so i improvised
class badFile {};
class badLine
{
public:
	badLine(int val)
		: line(val) {}
	int getLine() {return line;}
private:
	int line;
};
class badRes {};
class endFile{};

//checks a string if it is convertible to a number
bool isNum(const string& s)
{
	for (int i = 0; i < s.length(); ++i)
		if (!(isdigit(s[i]) || s[i] == 46))
			return false;
	return true;
}

//parses out an ip address from raw input from the stream
string cleanIP(string raw, const bool first)
{
	if (first)
		return raw.substr(1, raw.length()-3);
	return raw.substr(1, raw.length()-2);
}

//turns a boolean into a yes/no string
string tf(bool b)
{
	if (b)
		return "Yes";
	return "No";
}

//class representing a response time
class response
{
public:
	//constructors
	response()
		: isRes(false), val(0) {}
	response(double res)
		: isRes(true), val(res) {}
	response(string hostName, string ipAdd, double res)
		: isRes(true), host(hostName), ip(ipAdd), val(res) {}
	//getters
	double getVal() const {return val;}
	string getHost() const {return host;}
	string getIP() const {return ip;}
	bool ifRes() const {return isRes;}
	bool ifHost() const {return !(host == "");}
private:
	double val;
	bool isRes;
	string host;
	string ip;
};

//class representing a hop, or the final destination host
class hop
{
public:
	//constructors
	hop(int line)
		: hopNum(line) {}
	hop(string hostName, string ipAdd)
		: hopNum(0), host(hostName), ip(ipAdd) {}
	//getters
	int getNum() const {return hopNum;}
	string getIP() const {return ip;}
	string getHost() const {return host;}
	response getRes(int i) const {return r[i];}
	bool ifRes() const {return r[0].ifRes() || r[1].ifRes() || r[2].ifRes();}
	double getAvg() const
	{
		double total = 0;
		int count = 0;
		for (int i = 0; i < r.size(); ++i)
		{
			total += r[i].getVal();
			if (r[i].ifRes())
				++count;
		}
		if (count != 0)
			return total / count;
		return 0;
	}
	//mutators
	void addHostIP(string hostName, string ipAdd)
	{
		host = hostName;
		ip = ipAdd;
	}
	void addRes(response res) {r.push_back(res);}
private:
	int hopNum;
	vector<response> r;
	string ip;
	string host;
};

//class representing the results, this is where computation happens and is the object passed to final output stream
class results
{
public:
	//constructor and computation
	results(const vector<hop>& h)
		: longest(0), longPos(0)
	{
		total = h.size()-1;
		ifSuc = h[total].ifRes();
		if (ifSuc)
			fails = 0;
		else
			fails = 1;
		host = h[0].getHost();
		ip = h[0].getIP();
		for (int i = 1; i < total; ++i)
		{
			
			if (!h[i].ifRes())
				++fails;
			if (h[i].ifRes() && h[i+1].ifRes())
			{
				double diff = h[i+1].getAvg() - h[i].getAvg();
				if (diff > longest)
				{
					longest = diff;
					longPos = i;
				}
			}
			continue;
		}
	}
	//getters
	double getLongest() const {return longest;}
	int getPos() const {return longPos;}
	int getTotal() const {return total;}
	string getHost() const {return host;}
	string getIP() const {return ip;}
	bool ifSucc() const {return ifSuc;}
	int getFails() const {return fails;}
private:
	double longest;
	int longPos;
	int total;
	int fails;
	string host;
	string ip;
	bool ifSuc;
};

//ostream operator overload for results objects
ostream& operator<<(ostream& os, results r)
{
	return os << "Destination host: " << r.getHost() << endl
		<< "Destination IP: " << r.getIP() << endl
		<< "Successful?: " << tf(r.ifSucc()) << endl
		<< "# of total hops: " << r.getTotal() << endl
		<< "# of unresponsive hops: " << r.getFails() << endl
		<< "# of responsive hops: " << r.getTotal() - r.getFails() << endl
		<< "longest average hop: " << r.getPos() << " to " << r.getPos()+1 << endl;
}

//function that reads a response, with error checking
response readResponse(istream& is)
{
	string read;
	is >> read;
	if (read == "*")
		return response();
	else
	{
		string host, ip;
		double val;
		if (isNum(read))
		{
			host = read;
			val = atof(read.c_str());
			is >> read;
			if (read == "ms")
				return response(val);
			else if (read.length() != 2 && isNum(cleanIP(read, false)))
			{
				ip = cleanIP(read, false);
				is >> read;
				if (isNum(read))
				{
					val = atof(read.c_str());
					is >> read;
					if (read == "ms")
						return response(host, ip, val);
					throw badRes();
				}
				throw badRes();
			}
			else throw badRes();
		}
		else
		{
			host = read;
			is >> read;
			if (read.length() != 2 && isNum(cleanIP(read, false)))
			{
				ip = cleanIP(read, false);
				is >> read;
				if (isNum(read))
				{
					val = atof(read.c_str());
					is >> read;
					if (read == "ms")
						return response(host, ip, val);
					throw badRes();
				}
				throw badRes();
			}
			throw badRes();
		}
		throw badRes();
	}
	throw badRes();
}

//function that reads a line, with error checking and rough error placement identification
hop readLine(istream& is, int& max, const int& line)
{
	string read, host, ip;
	if (line == 0)
	{
		is >> read >> read >> host >> ip >> max >> read >> read >> read >> read >> read;
		if (!is || !isNum(cleanIP(ip, true)))
			throw badLine(line+1);
		else
			return hop(host, cleanIP(ip, true));
	}
	else 
	{
		int num;
		is >> read;
		if ((int)read[0] == 0)
			throw endFile();
		try
		{
			if (!isNum(read))
				throw badLine(line+1);
			num = atoi(read.c_str());
			if (num != line)
				throw badLine(line+1);
			hop h(line);
			for (int i = 0; i < 3; ++i)
				h.addRes(readResponse(is));
			h.addHostIP(h.getRes(0).getHost(), h.getRes(0).getIP());
			return h;
		}
		catch(badRes)
		{
			throw badLine(line+1);
		}
		catch(...)
		{
			cout << "Something unexpected has occured. Please restart the program." << endl;
			throw badLine(line+1);
		}
	}
}

//function that reads an entire file, with error checking
void readFile(istream& is, vector<hop>& voh, int& max)
{
	try
	{
		voh.push_back(readLine(is, max, 0));
		for (int i = 1; i <= max; ++i)
			voh.push_back(readLine(is, max, i));
	}
	catch(badLine& bl)
	{
		cout << "There is a bad line at line " << bl.getLine() << " in the file you specified, please check your input file." << endl;
		throw badFile();
	}
	catch(endFile)
	{
		return;
	}
	catch(...)
	{
		cout << "Wow, something really horrible has happened, what have you been doing to this program?" << endl;
		throw badFile();
	}
}

//writing function
void writeFile(ostream& ost, const results r)
{
	ost << r;
}

void entry(string& input);

//entry point
int main()
{

	
	int input;
	begin:
	cout << "Please input the corresponding number to the following options to make your choice:" << endl
		<< "1. Input name of file to read" << endl
		<< "2. Quit" << endl;
	if (cin)
	{
		cin >> input;
		switch(input)
		{
		case 1:
			{
				string file;
				
				clock_t t;
				t = clock();
				
				entry(file);
				cout << "Processing done! Your results will be in a file called output.txt." << endl;
				
				t = clock() - t;
				printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
				
				break;

				
			}
		case 2:
			return 0;
		default:
			cout << "You entered an invalid choice. Please try again." << endl << endl;
			cin.clear();
			cin.ignore();
			goto begin;
		}
	}
}

//handles input and file name entry
void entry(string& filename)
{
	input:
	int max;
	vector<hop> voh;
	cin >> filename;
	ifstream ist(filename.c_str());
	filename = "output.txt";
	ofstream ost(filename.c_str());
	try
	{
		readFile(ist, voh, max);
		results out(voh);
		writeFile(ost, out);
	}
	catch(badFile)
	{
		cout << "You have a bad file. It could be invalid, or it could just be wrongly formatted. Either way, I refuse to work for you until you give me a file I understand, which would make me happy. \n\nBut, please, do try again." << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		goto input;
	}
	catch(...)
	{
		cout << "You shouldn't be here. If you're here, it means that the apocalypse is nigh, and we are doomed. Have a good last day." << endl;
	}
}