// lab4.cpp : Defines the entry point for the console application.
//

#include "std_lib_facilities.h"

struct hero
{
	string hero_name;
	int health;
	int attack_damage;

	hero()
	{
		cout << "Please give a name to your hero:" << endl;
		cin >> hero_name;
		cout << "Please specify the amount of health your hero has:" << endl;
		cin >> health;
		cout << "Please specify the attack damage of your hero:" << endl;
		cin >> attack_damage;
	}

	void decreaseHealth(int h)
	{
		if (health-h < 0)
			health = 0;
		else
			health = health-h;
	}

	int getAttack()
	{
		cout << "Attack damage: " << attack_damage << endl;
	}

	void printInfo()
	{
		cout << "Name: " << hero_name << endl;
		cout << "Health: " << health << endl;
	}

};


struct enemies
{
	int x, y;
	vector<vector<int>> mat;

	enemies()
	{
		cout << "Please input 2 integers to define the size of the enemy wave:" << endl;
		cin >> x >> y;
		for (int i = 0; i < x; ++i)
		{
			mat.push_back(vector<int>(y));
			for (int j = 0; j < y; ++j)
				mat[i][j] = i+1;
		}
	}

	void showWave()
	{
		for (int i = 0; i < mat.size(); ++i)
		{
			cout << "[";
			for (int j = 0; j < mat[0].size(); ++j)
				cout << mat[i][j] << " ";
			cout << "\b]" << endl;
		}
	}
};		

int main()
{
	hero h;

	enemies wave;
	wave.showWave();
	
	//while(h.health != 0)
	//{
	//	h.decreaseHealth(10);
	//	h.printInfo();
	//}
	
	return 0;
}

