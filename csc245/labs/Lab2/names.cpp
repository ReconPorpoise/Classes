
#include <string>
#include <iostream>
using namespace std;

void BreakDown (string name, string& first, string& last, string& mi);
int main()
{
	string name, first, last, mi;

	cout << "Name? <Last, First MI.> ";
	getline (cin, name);
		
	BreakDown (name, first, mi, last);

	cout << "First Name Entered :  " << first << endl;
	cout << "Last Name Entered :  " << last << endl;
	cout << "Middle Initial Entered :  " << mi << endl;
	return 0;
}

void BreakDown (string name, string& first, string& mi, string& last)
{
	// pre  : name is initialized with a full name
	// post : first, mi, and last contain the individual components
        //        of that name

        // find comma to separate last name  
	int posComma = name.find(",");
	// find position of the . - 1 to get position of middle initial
	int posMI = name.find(".") - 1;
	// last name is 0 to the comma
	last = name.substr(0, posComma);
	// first name is comma + 2 because ", space" and the length of it is the index of the middle initial - 1 (white space) - 	the comma space + 2. This gets anything after ", " and before " X."
	first = name.substr(posComma + 2, ((posMI - 1) - (posComma + 2))); 
	mi = name.substr(posMI, 1);	
} 
