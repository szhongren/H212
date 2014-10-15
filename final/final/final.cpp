// final.cpp : Defines the entry point for the console application.
//

#include "../../std_lib_facilities.h"

struct B
{
	virtual void f() const {cout << "b,f" << endl;}
	void g() const {cout << "b,g" << endl;}

};

struct D : B
{
	void f() const { cout << "d,f" << endl;}

	void g() const { cout << "d,g" << endl;}
};

void call(const B& b)
{
	b.f();
	b.g();
}

int main()
{
	list<int> v(10);
	list<int>::iterator it = v.begin();
	it -= 1;
	cout << it[2];
}

