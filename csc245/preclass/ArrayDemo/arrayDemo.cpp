#include <iostream>
#include <vector>
#include <cstdlib>

// Generate numbers (1-100)
// Print number of occurrences of each number
int main()
{
	const int DIFFERENT_NUMBERS = 100;
	
	// Prompt for and read number of games.
	int totalNumbers;
	std::cout << "How many numbers to generate?: ";
	std::cin >> totalNumbers;

	std::vector<int> numbers( DIFFERENT_NUMBERS + 1 );

	// Initialize the vector to zeros.
	for( int i = 0; i < numbers.size(); i++ )
		numbers[ i ] = 0;

	// Generate the numbers.
	for( int j = 0; j < totalNumbers; j++ )
		numbers[ rand() % DIFFERENT_NUMBERS + 1 ]++;

	// Output the summary.
	for( int k = 1; k <= DIFFERENT_NUMBERS; k++ )
		std::cout << k << " occurs " << numbers[ k ] << " time(s) \n";
	
	return 0;
}
