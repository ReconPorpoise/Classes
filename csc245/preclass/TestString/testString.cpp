#include <iostream>
#include <string>

int main()
{
	std::string a = "hello";
	std::string b = "world";
	std::string c;			// Should be ""

	c = a + " ";			// Should be "hello "
	c += b;				// Should be "hello world"
	
	// Print c the easy way.
	std::cout << "c is: " << c << std::endl;
	
	// Print c the primative way.
	std::cout << "c is: " << c.c_str() << std::endl;

	// Print c character-by-character
	std::cout << "c is: ";
	for( int i = 0; i < c.length(); i++ )
		std::cout << c[ i ];
	std::cout << std::endl;

	return 0;
}
