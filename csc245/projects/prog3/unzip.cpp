#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

void decode( string file );

int main( int argc, char* argv[ ] )
{
	string fileName;
	
	// checks for no command line arguments
	if( argv[ 1 ] != NULL )
		fileName = argv[ 1 ];
	// if nothing, print out a message and kill unzip
	else {
		cout << "Bad input. Try again." << endl;
		return 0;
	}

	// otherwise, check if the file exists then let them know		
	ifstream infile;
	infile.open( fileName );
	if( !infile ) {
		cout << "File " << fileName << " does not exist. Try again." << endl;
		return 0;
	}
	infile.close();

	decode( fileName );
	
	return 0;
}

void decode( string file )
{
	// opens the file for tokenization
	ifstream infile;
	infile.open( file );

	// gets the number of different characters that have to be mapped
	string numChars;
	getline( infile, numChars );

	// plainText holds the decompressed string
	string plainText = "";
	// code holds the temporary encoded character for map lookup
	string code = "";

	// creates association between encoded string and ascii character
	map< string, int > codes;
	string encoded;
	while( getline( infile, encoded ) ) {
		// all pairs have a space between, so if there is a space...
		// split the string. The left side is the ascii and the right
		// is the encoding for the character	
		int space = encoded.find( ' ' );
		if( space != -1 ) {
			string asciiStr = encoded.substr( 0, space );
			string encoding = encoded.substr( space + 1 );
			int ascii = stoi( asciiStr );

			// add the pair to the map so we can find and add ascii characters
			// using the encoding found in the last line of the input file
			codes[ encoding ] = ascii;
		}
		// this is for the last line only (no space in the encoded string)
		else {
			// parse each character in the encoded string...
			for( int i = 0; i < encoded.length(); i++ ) {
				// add it to the temp string which holds the current encoding
				// key in the encoded string
				code += encoded[ i ];
				// if that encoding/key exists in the map, add that ascii 
				// character's plainText character to the plainText string
				if( codes.find( code ) != codes.end() ) {
					plainText += char( codes[ code ] );
					// reset the variable to get the next encoding string	
					code = "";
				}			 
			}
		}
	}
	infile.close();	
	
	// separates the .zip from the file name
	int extension = file.find( '.' );
	// creates a new file with the original name sans-.zip
	string newFile = file.substr( 0, extension );
	ofstream outFile( newFile );
	// add the plainText/decoded string to the file and close it
	outFile << plainText;
	outFile.close();

	// friendly message to alert user that the file has been decompressed
	cout << "File successfully decompressed back to original size." << endl;
}
