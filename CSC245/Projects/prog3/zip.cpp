#include <algorithm>
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include "huffman.h"
using namespace std;

void fileCheck( int argl, char** args );
void insertNodes( string fileName, int Letters[ ], HuffmanTree tree, string flag );
void printHelp( );
void createNewFile( HuffmanTree tree, string fileName, int Letters[ ]);
//void PrintLetters ( const int Letters[ ] );

const int NumLetters = 256;

int main( int argc, char** argv )
{
    fileCheck( argc, argv );

    return 0;
}

void fileCheck( int argl, char** args ) {
    HuffmanTree tree;
    int Letters[ NumLetters ];

    if( argl == 3 ) {
        // Remove all spaces from the argument
        string flag = args[ 1 ];

        // if they want the table printed or a help option, catch it and respond accordingly
        if( flag == "--t" ) {
            string fileName = args[ 2 ];
            ifstream infile;
            infile.open( fileName );

            if( !infile ) {
                cout << "File " << fileName << " does not exist." << endl;
                return;
            }
            infile.close();
            insertNodes( fileName, Letters, tree, flag );
        }
        else if( flag == "--help" ) {
            string fileName = args[ 2 ];
            ifstream infile;
            infile.open( fileName );

            if( !infile ) {
                cout << "File " << fileName << " does not exist." << endl;
                return;
            }
            infile.close();
            printHelp();
        }
        else {
            cout << "Incorrect flag. Try again." << endl;
            return;
        }
    }
    // if there is only one argument then they must have only input the file name
    else if( argl == 2 ) {
        string flag = args[ 1 ];
        if( flag == "--help" )
            printHelp();
        else {
            string fileName = args[ 1 ];
            
            ifstream infile;
            infile.open( fileName );
            if( !infile ) {
                cout << "File " << fileName << " does not exist." << endl;
                return;
            }
            infile.close();

            string flag = "nothing";
            insertNodes( fileName, Letters, tree, flag );
        }
    }
    else
        cout << "Invalid input format. \nTry './ZIP --help' for running help." << endl;
}

void printHelp( ) {
    ifstream helpFile;
    string curr;
    helpFile.open( "help" );

    while( getline( helpFile, curr ) ) {
        cout << curr << endl;
    }
}

void insertNodes( string fileName, int Letters[ ], HuffmanTree tree, string flag )
{
	char ch;

    // initialize an array of size 126 to hold all ascii values
	for ( char ch = char( 0 );  ch <= char( 126 );  ch++ )
		Letters[ ch ] = 0;

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
    if( flag == "--t" )
        tree.PrintTable();

    createNewFile( tree, fileName, Letters );
}

void createNewFile( HuffmanTree tree, string fileName, int Letters[ ] ) {
	string newFile = fileName + ".zip";
	ofstream outFile( newFile );
    string encoded = "";

    ifstream infile;
    infile.open( fileName );
    string curr;
    
    int numChar = ( tree.numNodes() + 1 ) / 2;
    outFile << numChar << endl;

    while( getline( infile, curr ) ) 
        for( int i = 0; i < curr.length(); i++ )
            encoded += tree.GetCode( curr[ i ] );
            
    outFile << encoded;
	outFile.close();
}