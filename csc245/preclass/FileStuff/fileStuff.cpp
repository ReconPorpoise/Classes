#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	ifstream infile( "infile.in" );
	ofstream outfile( "outfile.out ");

	int num;
	string s;
	
	// While the file still has numbers: 
	// if the numebr is not 0, output it, else break.
	while( infile >> num )
		if( num != 0 )
			outfile << num << " ";
		else 
			break;

	// Get the line in the file then send it out to the output file
	getline(infile, s);
	outfile << endl << s << endl;k
	return 0;
}
