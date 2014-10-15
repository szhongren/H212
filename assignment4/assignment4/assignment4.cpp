//Zhongren Shao, shaoz
//assignment 4

#include "std_lib_facilities.h"

struct vals
{
	vector<double> vec;
	double max;
	double min;
	double mean;
	double median;

	//vals constructor that takes an int argument for the size of the vector
	vals(int size)
	{
		//for use of median as a temporary variable to calculate mean
		median = 0;
		cout << "Please input your values:" << endl;
		int i = 0;
		while (i < size)
		{
			static double temp;
			if (cin >> temp)
			{
				++i;
				vec.push_back(temp);
			}
			//error checking
			else
			{
				cout << "Wrong type of input, please try again." << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
		}
	}

	//output function, outputs all the variables for the struct
	void out()
	{
		cout << "Largest: " << max << endl
			<< "Smallest: " << min << endl
			<< "Mean: " << mean << endl
			<< "Median: " << median << endl;
	}

	//function that takes a pointer to the vals struct in question and finds and instantiates the values we are interested in within the struct
	void valFinder()
	{
		//sorting the vector
		int size = vec.size();
		sort(vec.begin(), vec.end());

		//finds the max and min
		max = vec[size - 1];
		min = vec[0];

		//finds the mean, using the median as a temporary storage value
		for (int i = 0; i < size; ++i)
		{
			median += vec[i];
		}
		mean = median/size;

		//finds the median
		if (size % 2 == 0)
			median = (vec[size/2] + vec[size/2-1])/2;
		else
			median = vec[size/2];
	}
};

int main()
{
	int size;
	cout << "Please specify the number of values that you want to input:" << endl;
	cin >> size;

	vals v(size);
	v.valFinder();
	v.out();
}