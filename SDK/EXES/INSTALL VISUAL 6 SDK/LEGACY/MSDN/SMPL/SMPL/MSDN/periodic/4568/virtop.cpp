////////////////////////////////////////////////////////////////
// VIRTOP Copyright 1995 Microsoft Systems Journal. 
// Simple program to demonstrate "virtual" operator<<.
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// To compile, type
//
//    cl virtop.cpp
//
// at the DOS prompt.

#include <iostream.h>

//////////////////
// Base class has friend operator and virtual protected print function.
//
class Fruit {
protected:
   virtual void print(ostream& os) const = 0;
public:
   friend ostream& operator<< (ostream& os, const Fruit& fruit);
};

//////////////////
// Derived classes implement their own print functions
//
class Apple : public Fruit {
protected:
   virtual void print(ostream& os) const { os << "apple"; }
};
   
class Orange : public Fruit {
protected:
   virtual void print(ostream& os) const { os << "orange"; }
};

////////////////
// There's just one operator<<
// It calls the virtual print function to do the work.
//
inline ostream& operator<< (ostream& os, const Fruit& fruit)
{
   fruit.print(os);
   return os;
}

////////////////
// Main program entry
//
int main()
{
   Apple  a;
   Orange o;
   Fruit* array[2] = { &a, &o };

	// print the fruits using operator<<
   for (int i=0; i<2; i++)
      cout << "Fruit #" << i << " is a " << *array[i] << "\n";

   return 0;
}
