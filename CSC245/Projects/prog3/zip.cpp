#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include "huffman.h"
using namespace std;

void CountLetters ( string fileName, int Letters[ ] );
void PrintLetters ( const int Letters[ ] );

const int NumLetters = 256;

int main( int argc, char* argv[ ] )
{
    HuffmanTree tree;
    string fileName;
    if( argv[ 2 ] != NULL ) {
        // Remove all spaces from the argument
        string flag = argv[ 1 ];
        for( int i = 0; i < flag.length(); i++ ) {
            if( flag[ i ] == ' ' ) {
                flag.erase( i, 1 );
            }      
        }
        // if they want the table printed or a help option, catch it and respond accordingly
        if( flag == "--t" )
            //do smthing
            cout << endl;  
        else if( flag == "help" )
            //do smthing
            cout << endl;
        else 
            //dosmthing
            cout << endl;
        fileName = argv[ 2 ];
    }
    // if there is only one argument then they must have only input the file name
    else if( argv[ 1 ] != NULL ) {
        fileName = argv[ 1 ];
    }
    
    int Letters[NumLetters]; 

	CountLetters ( fileName, Letters );
	PrintLetters ( Letters );

    return 0;
}

void CountLetters ( string fileName, int Letters[ ] )
{
	char ch;

	for (char ch = char(0);  ch <= char(126);  ch++)
		Letters[ch] = 0;

	ifstream infile;
    infile.open( fileName );
    
    string curr;
    while( getline( infile, curr ) ) {
        for( int i = 0; i < curr.length(); i++ ) {
            Letters[ curr[ i ] ]++;
        }
        Letters[ '\n' ]++;
    }
}


void PrintLetters ( const int Letters[ ] )
{
	for (char ch = char(0);  ch <= char(126);  ch++)
	  if ( (Letters[ch] != 0) && (ch != '\n') && (ch != ' ') )
	    cout << "Char " << ch << " appearances  : " << Letters[ch] << endl;
	  else if ( (Letters[ch] != 0) && (ch == '\n') )
	    cout << "Char nl appearances : " << Letters[ch] << endl;
	  else if ( (Letters[ch] != 0) && (ch == ' ') )
	    cout << "Char sp appearances : " << Letters[ch] << endl;
}
