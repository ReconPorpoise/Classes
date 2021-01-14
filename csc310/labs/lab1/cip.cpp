/*
 * Ronald Karamuca
 * 1-13-2021
 * CSC 310 Lab 1: Back in the Saddle Again
 * Part 3: Classes, Inheritance, and Polymorphism
 * Uses virtual to enable inheritance and polymorphism
 * then creates objects of those classes for demonstration.
 */
#include <iostream>
using namespace std;

class Base
{
	public:
		virtual void iam();
};

void Base::iam()
{
	cout << "base" << endl;
}

// class derived from Base
class ExtraOne : public Base {
	public:
		// overloaded iam()
		void iam() {
			cout << "iam one" << endl;
		}
		// iam2() calls base iam()
		void iam2() {
			Base::iam();
		}
};

// class derived from Base
class ExtraTwo : public Base {
	public:
		// overloaded iam()
		void iam() {
			cout << "iam two" << endl;
		}
		// iam2() calls base iam()
		void iam2() {
			Base::iam();
		}
};

int main() 
{
	// create object of class Base and call its iam()
	Base base;
	base.iam();

	// create object of class ExtraOne and call its iam() and iam2()
	// iam2() should be the same as Base and iam() should be overloaded
	ExtraOne eone;
	eone.iam();
	eone.iam2();

	// create object of class ExtraTwo and call its iam() and iam2()
	// iam2() should be the same as Base and iam() should be overloaded
	ExtraTwo etwo;
	etwo.iam();
	etwo.iam2();

	// create pointers to the derived-class objects and call their methods using them
	Base *eoneP = &eone;
	Base *etwoP = &etwo;
	eoneP -> iam();
	etwoP -> iam();

	return 0;
}
