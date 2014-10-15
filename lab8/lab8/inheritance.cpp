#include <iostream>

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
class Dog : protected animal
{
protected:
	Dog()
		: weight(50);
	{
		setName("Dog");
	}
	string getThreats() const { return "rabies and bites"; }
	virtual string getFurCol() const { return furcolor; }
	virtual int getWeight() const { return weight; }
	virtual void setWeight() =0;
private:
	string furcolor;
	int weight;
}

class Corgi : protected Dog
{
protected:
	Corgi() { setName("Corgi"); }
	string getFurCol() const { return furcolor; }
	int getWeight() const { return weight; }
	void setWeight() { weight -= 5; }
}

class GoldenRetriever : protected Dog
{
protected:
	GoldenRetriever()
		: furColor("gold")
	{
		setName("Golden Retriever");
	}
	string getFurCol() const { return furcolor; }
	int getWeight() const { return weight; }
	void setWeight() { weight += 20; }
}

void dogOut(const Dog& d)
{
	cout << "furCol: " << d.getFurCol() << endl;

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
  Bird b;
  Cardinal c;
  Robin r;

  cout << a << endl;
  cout << c << endl;

  outputBird(c);
  outputBird(r);
}