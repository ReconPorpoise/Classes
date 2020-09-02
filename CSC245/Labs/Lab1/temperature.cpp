#include <iostream>

double convert( double temp );

int main()
{
	// Preps the celsius variable to be given a value via std::cin
	double celsius;
	std::cout << "Enter a Celsius value to convert to Fahrenheit: ";
	std::cin >> celsius;
	
	// Prints the string that shows the C to F conversion
	std::cout << celsius << " degrees Celsius is " << convert( celsius ) << " degrees Fahrenheit." << std::endl;
	return 0;
}

double convert( double temp )
{
	// returns the converted temp to be std::cout in main
	return( 1.8 * temp + 32);
}
