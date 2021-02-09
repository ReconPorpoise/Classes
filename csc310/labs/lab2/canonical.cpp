#include <iostream>
#include <string>
using namespace std;

int convert(string date);
int getDate(string month);

int main(int argc, char** argv)
{
	string date;
	// allows user to enter the date via command-line-arguments
	// or via cin.
	if(argc == 1) {
		cout << "Enter a date to be converted to canonical form: ";
		getline(cin, date);
	}
	else {
		date += argv[1];
		date += " ";
		date += argv[2];
		date += " ";
		date += argv[3];
	}
	
	// converts the date to canonical
	int canon = convert(date);
	// if we get a -1, the input was bad.
	// let the user know
	if(canon == -1) {
		cout << "Bad month input. Please try again." << endl;
		return 1;
	}
	else
		cout << "Here is the canonical form: " << to_string(canon) << endl;
	return 0;
}

int convert(string date) 
{
	string canon = "";

	// gets the first piece (month)	
	int space = date.find(' ');
	canon += to_string(getDate(date.substr(0, space)));
	date.erase(0, space + 1);
	if(canon == "-1")
		return -1;

	// gets the second piece (day)
	space = date.find(' ');
	canon += date.substr(0, space - 1);
	date.erase(0, space + 1);

	// gets the third piece (year)
	canon += date.substr(0, date.length());

	return stoi(canon);
}

// converts the month to a number
int getDate(string month) 
{
	if(month == "January")
		return 1;
	else if(month == "February")
		return 2;
	else if(month == "March")
		return 3;
	else if(month == "April")
		return 4;
	else if(month == "May")
		return 5;
	else if(month == "June")
		return 6;
	else if(month == "July")
		return 7;
	else if(month == "August")
		return 8;
	else if(month == "September")
		return 9;
	else if(month == "October")
		return 10;
	else if(month == "November")
		return 11;
	else if(month == "December")
		return 12;
	return -1;
}


