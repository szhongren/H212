#include "../../std_lib_facilities.h"

using namespace std;

// Most senior parent class
class Animal {
  string name;
public:
  Animal() { setName("Animal"); }
  void setName (string n) { name = n; }
  string getName() const { return name; }

  virtual string getThreats() const { return "unknown"; }
};

//dog class
class Dog : public Animal
{
public:
	Dog() {	setName("Dog"); }
	string getThreats() const { return "rabies and dog-eating people"; }
	virtual string getFurCol() const =0;
	virtual int getWeight() const =0;
	virtual int setWeight() const =0;
protected:
	string furcolor;
	int weight;
};

class Corgi : public Dog
{
public:
	Corgi()
	{
		weight = 30;
		furcolor = "corgi fur color";
		setName("Corgi");
	}
	string getFurCol() const { return furcolor; }
	int getWeight() const { return weight; }
	int setWeight() const  { return weight - 5; }
};

class GoldenRetriever : public Dog
{
public:
	GoldenRetriever()
	{
		weight = 50;
		furcolor = "gold";
		setName("Golden Retriever");
	}
	string getFurCol() const { return furcolor; }
	int getWeight() const { return weight; }
	int setWeight() const { return weight + 20; }
};

void dogOut(const Dog& d)
{
	cout << "This is a " << d.getName() << " and it has a weight of " << d.getWeight() << "." << endl
		<< "The value returned when setweight is run is " << d.setWeight() << " and its fur color is " << d.getFurCol() << endl
		<< "They are all threatened by " << d.getThreats() << endl;
}

// Child class of Animal
class Bird : public Animal{
public:
  Bird () { setName("Bird"); }
  string getThreats() const { return "Six-Pack soda holders :("; }
  virtual string getNickname() const { return "Bird"; }
};

// Child class of Bird
class Cardinal : public Bird {
public:
  Cardinal () { setName("Cardinal"); }
  string getNickname() const { return "Red Bird"; }
};

// Child class of Bird
class Robin : public Bird {
public:
  Robin() { setName("Robin"); }
  // I kid you not, this is the biological name for the Robin
  string getNickname() const { return "Turdus migratorius"; }
  string getThreats() const { return "Extreme Pollution"; }
};

// helper function to output Bird and Bird children objects
void outputBird(const Bird& b){
  cout << b.getName() << ", aka: " << b.getNickname() << ", is threatened by " <<
    b.getThreats() << "\n";
}

// easy way to output animal threats
ostream& operator<<(ostream& os, const Animal& a) {
  return os << a.getName() << " is threatened by " << a.getThreats();
}

int main() {
  Animal a;
  GoldenRetriever g;
  Corgi c;

  dogOut(g);
  dogOut(c);
}