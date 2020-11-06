#include <algorithm>
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include "huffman.h"
using namespace std;

bool fileCheck( char** args );
void insertNodes( string fileName, int Letters[ ], HuffmanTree tree );
//void PrintLetters ( const int Letters[ ] );

const int NumLetters = 256;

int main( int argc, char** argv )
{
    fileCheck( argv );

    //insertNodes( fileName, Letters, tree );
    return 0;
}

bool fileCheck( char** args ) {
    string fileName;
    HuffmanTree tree;
    int Letters[ NumLetters ];

    if( args[ 2 ] != NULL ) {
        // Remove all spaces from the argument
        string flag = args[ 1 ];
        for( int i = 0; i < flag.length(); i++ ) {
            if( flag[ i ] == ' ' ) {
                flag.erase( i, 1 );
            }      
        }

        // if they want the table printed or a help option, catch it and respond accordingly
        if( flag == "--t" )
            // do smthing
            cout << endl;
        else if( flag == "help" )
            //do smthing
            cout << endl;
        else 
            cout << "Incorrect flag. Try again." << endl;
        fileName = args[ 2 ];
    }
    // if there is only one argument then they must have only input the file name
    else if( args[ 1 ] != NULL ) {
        fileName = args[ 1 ];
    }
}

void insertNodes( string fileName, int Letters[ ], HuffmanTree tree )
{
	char ch;

    // initialize an array of size 126 to hold all ascii values
	for (char ch = char(0);  ch <= char(126);  ch++)
		Letters[ch] = 0;

	ifstream infile;
    infile.open( fileName );
    
    // gets weight of each letter in the alphabet
    string curr;
    while( getline( infile, curr ) ) {
        // if it's in the string, increment its count in the array
        for( int i = 0; i < curr.length(); i++ )
            Letters[ curr[ i ] ]++;
        Letters[ '\n' ]++;
    }

    // if the number exists, insert that node into the Huffman Tree
    for( char ch = char( 0 ); ch <= char( 126 ); ch++ )
        if( Letters[ ch ] != 0 ) 
            tree.insert( ch, Letters[ ch ] );

    // build the tree with inserted nodes
    tree.build();
}