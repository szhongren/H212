#include "std_lib_facilities.h"

// ------------------------------------------------------------------------
/* */
// EXAMPLE 1
// SIMPLE SINGLE INHERITANCE

class Shape  {
public:
  double area () { return 0; };
};

class Circle : public Shape {
protected:
  double radius;
public:
  Circle (double _radius) : radius(_radius) {}
  double area () { return 3.14 * radius * radius; }
};

class Rectangle : public Shape {
protected:
  double side1, side2;
public:
  Rectangle (double _side1, double _side2) : side1(_side1), side2(_side2) {}
  double area () { return side1*side2; }
};

class Square : public Rectangle {
public:
  Square (double _side) : Rectangle(_side,_side) {}
};


int main (int argc, char *argv[])
{
  Circle c(2);
  Shape& p1(c);
  cout << "Circle's area (through shape)  = " << p1.area() << endl;
  cout << "Circle's area (through circle) = " << c.area() << endl;

  Rectangle r(1,2);
  Shape& p2(r);
  cout << "Rectangle's area (through shape)     = " << p2.area() << endl;
  cout << "Rectangle's area (through rectangle) = " << r.area() << endl;

  Square s(2);
  Shape& p3(s);
  Rectangle& p4(s);
  cout << "Square's area (through shape)     = " << p3.area() << endl;
  cout << "Square's area (through rectangle) = " << p4.area() << endl;
  cout << "Square's area (through square)    = " << s.area() << endl;

}
// ------------------------------------------------------------------------

/*
// ------------------------------------------------------------------------
// EXAMPLE 2
// SINGLE INHERITANCE WITH VIRTUAL METHODS IN BASE CLASS

class Shape  {
public:
  virtual double area () { return 0; };
};

class Circle : public Shape {
protected:
  double radius;
public:
  Circle (double _radius) : radius(_radius) {}
  double area () { return 3.14 * radius * radius; }
};

class Rectangle : public Shape {
protected:
  double side1, side2;
public:
  Rectangle (double _side1, double _side2) : side1(_side1), side2(_side2) {}
  double area () { return side1*side2; }
};

class Square : public Rectangle {
public:
  Square (double _side) : Rectangle(_side,_side) {}
};


int main (int argc, char *argv[])
{
  Circle c(2);
  Shape& p1(c);
  cout << "Circle's area (through shape)  = " << p1.area() << endl;
  cout << "Circle's area (through circle) = " << c.area() << endl;

  Rectangle r(1,2);
  Shape& p2(r);
  cout << "Rectangle's area (through shape)     = " << p2.area() << endl;
  cout << "Rectangle's area (through rectangle) = " << r.area() << endl;

  Square s(2);
  Shape& p3(s);
  Rectangle& p4(s);
  cout << "Square's area (through shape)     = " << p3.area() << endl;
  cout << "Square's area (through rectangle) = " << p4.area() << endl;
  cout << "Square's area (through square)    = " << s.area() << endl;
}
// ------------------------------------------------------------------------
*/

/*
// ------------------------------------------------------------------------
// EXAMPLE 3
// SINGLE INHERITANCE WITH VIRTUAL METHODS IN BASE AND DERIVED CLASSES
// If you comment out the virtual keyword in Shape, and keep the virtual
// keyword in Rectangle, then only Rectangle's (and subsequently derived
// classes') area is virtual.  But, if you make Shape::area virtual, then
// it is always virtual irrespective of the virtual keyword in any derived
// classes.

class Shape  {
public:
  // virtual 
  double area () { return 0; };
};

class Circle : public Shape {
protected:
  double radius;
public:
  Circle (double _radius) : radius(_radius) {}
  double area () { return 3.14 * radius * radius; }
};

class Rectangle : public Shape {
protected:
  double side1, side2;
public:
  Rectangle (double _side1, double _side2) : side1(_side1), side2(_side2) {}
  // Note the "virtual"
  virtual double area () { return side1*side2; }
};

class DoubleSquare : public Rectangle {
public:
  DoubleSquare (double _side) : Rectangle(_side,_side) {}
  double area () { return 2*side1*side2; }
};


int main (int argc, char *argv[])
{
  Circle c(2);
  Shape& p1(c);
  cout << "Circle's area (through shape)  = " << p1.area() << endl;
  cout << "Circle's area (through circle) = " << c.area() << endl;

  Rectangle r(1,2);
  Shape& p2(r);
  cout << "Rectangle's area (through shape)     = " << p2.area() << endl;
  cout << "Rectangle's area (through rectangle) = " << r.area() << endl;

  DoubleSquare s(2);
  Shape& p3(s);
  Rectangle& p4(s);
  cout << "Double square's area (through shape)         = " << p3.area() << endl;
  cout << "Double square's area (through rectangle)     = " << p4.area() << endl;
  cout << "Double square's area (through double square) = " << s.area() << endl;
}
// ------------------------------------------------------------------------
*/

/*
// ------------------------------------------------------------------------
// EXAMPLE 4
// SINGLE INHERITANCE WITH PURE VIRTUAL METHODS IN BASE CLASS
class Shape  {
public:
  // pure virtual function
  virtual double area () = 0;
};

class Circle : public Shape {
protected:
  double radius;
public:
  Circle (double _radius) : radius(_radius) {}
  double area () { return 3.14 * radius * radius; }
};

class Rectangle : public Shape {
protected:
  double side1, side2;
public:
  Rectangle (double _side1, double _side2) : side1(_side1), side2(_side2) {}
  double area () { return side1*side2; }
};

class Square : public Rectangle {
public:
  Square (double _side) : Rectangle(_side,_side) {}
};


int main (int argc, char *argv[])
{
  Circle c(2);
  Shape& p1(c);
  cout << "Circle's area (through shape)  = " << p1.area() << endl;
  cout << "Circle's area (through circle) = " << c.area() << endl;

  Rectangle r(1,2);
  Shape& p2(r);
  cout << "Rectangle's area (through shape)     = " << p2.area() << endl;
  cout << "Rectangle's area (through rectangle) = " << r.area() << endl;

  Square s(2);
  Shape& p3(s);
  Rectangle& p4(s);
  cout << "Square's area (through shape)     = " << p3.area() << endl;
  cout << "Square's area (through rectangle) = " << p4.area() << endl;
  cout << "Square's area (through square)    = " << s.area() << endl;

  // The following line will NOT compile, since Shape is an abstract base class
  // Shape shape;
}
// ------------------------------------------------------------------------
*/

/*
// ------------------------------------------------------------------------
// EXAMPLE 5
// MULTIPLE INHERITANCE

class Shape {
public:
  double area () { return 0; };
};

class Color {
protected:
  string color;
public:
  Color (string _color) : color(_color) {}
  string getColor () { return color; }
};

class Circle : public Shape, public Color {
protected:
  double radius;
public:
  Circle (double _radius, string _color) : radius(_radius), Color(_color) {}
  double area () { return 3.14 * radius * radius; }
};

class Rectangle : public Shape {
protected:
  double side1, side2;
public:
  Rectangle (double _side1, double _side2) : side1(_side1), side2(_side2) {}
  double area () { return side1*side2; }
};

class Square : public Rectangle, public Color {
public:
  Square (double _side, string _color) : Rectangle(_side,_side), Color(_color) {}
};


int main (int argc, char *argv[])
{
  Circle c(2, "red");
  cout << "Circle's color  = " << c.getColor() << endl;

  Square s(2, "green");
  Rectangle& p(s);
  cout << "Square's color (through square)    = " << s.getColor() << endl;
  // The following statement will not compile
  // cout << "Square's color (through rectangle) = " << p.getColor() << endl;
}
// ------------------------------------------------------------------------
*/

/*
// ------------------------------------------------------------------------
// EXAMPLE 6
// MULTIPLE INHERITANCE WITH A COMMON BASE CLASS
// Note the there are two copies of the Object base class, one through Shape
// and another through Color.
//  Object        Object
//    \             /
//     \           /
//     Shape    Color
//       \       /
//        \     /
//        Circle

class Object {
private:
  static int count;
protected:
  int ID;
public:
  Object () { ID = ++count; }
  int getID () { return ID; }
};
// Note how static variables have to be initialized OUTSIDE the class definition
int Object::count = 0;

class Shape : public Object {
public:
  double area () { return 0; };
};

class Color : public Object {
protected:
  string color;
public:
  Color (string _color) : color(_color) {}
  string getColor () { return color; }
};

// Flip the order of "Shape" and "Color" below and observe how object IDs change
class Circle : public Color, public Shape {
protected:
  double radius;
public:
  Circle (double _radius, string _color) : radius(_radius), Color(_color) {}
  double area () { return 3.14 * radius * radius; }
};

int main (int argc, char *argv[])
{
  Circle c(2, "red");
  Shape& p1(c);
  Color& p2(c);
  // The next statement will NOT compile because which getID() to call is unclear
  // cout << "Circle's object ID (through circle) = " << c.getID() << endl;
  cout << "Circle's object ID (through shape)  = " << p1.getID() << endl;
  cout << "Circle's object ID (through color)  = " << p2.getID() << endl;
}
// ------------------------------------------------------------------------
*/

/*
// ------------------------------------------------------------------------
// EXAMPLE 7
// MULTIPLE INHERITANCE WITH VIRTUAL BASE CLASSES
// Making a base class "virtual" (in a derived class) tells the compiler to 
// keep only ONE copy of that base class in all subsequently derived classes.  
// This is also called DIAMOND hierarchy, because of the way it looks.
//      Object
//      /    \
//     /      \
//   Shape   Color
//     \       /
//      \     /
//      Circle
//

class Object {
private:
  static int count;
protected:
  int ID;
public:
  Object () { ID = ++count; }
  int getID () { return ID; }
};
// Note how static variables have to be initialized OUTSIDE the class definition
int Object::count = 0;

class Shape : virtual public Object {
public:
  double area () { return 0; };
};

class Color : virtual public Object {
protected:
  string color;
public:
  Color (string _color) : color(_color) {}
  string getColor () { return color; }
};

class Circle : public Shape, public Color {
protected:
  double radius;
public:
  Circle (double _radius, string _color) : radius(_radius), Color(_color) {}
  double area () { return 3.14 * radius * radius; }
};

int main (int argc, char *argv[])
{
  Circle c(2, "red");
  Shape& p1(c);
  Color& p2(c);
  // Note that the next statement WILL compile now because call to getID 
  // is unambiguous
  cout << "Circle's object ID (through circle) = " << c.getID() << endl;
  cout << "Circle's object ID (through shape)  = " << p1.getID() << endl;
  cout << "Circle's object ID (through color)  = " << p2.getID() << endl;
}
// ------------------------------------------------------------------------
*/
