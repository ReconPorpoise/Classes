#include <iostream>

void printMe();		// Function Prototype ("Declaration")
			// Note : All Prototypes Go Prior to Main
			// 	  They are just function header with a 
			// 	  semicolon attached
			
int main() 
{
	printMe();
	return 0;
}

void printMe()
{
	std::cout << "Hello World!" << std::endl;
}
