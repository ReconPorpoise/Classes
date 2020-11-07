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

const int NumLetters = 256;

int main( int argc, char** argv )
{
    fileCheck( argc, argv );

    return 0;
}

void fileCheck( int argl, char** args ) {
    HuffmanTree tree;
    int Letters[ NumLetters ];

    // if there is a flag...
    if( argl == 3 ) {
        // flag is the second element in the argv array
        string flag = args[ 1 ];

        // if they want the table printed or a help option, catch it and respond accordingly
        if( flag == "--t" ) {
            // check if file is valid after --t is caught... then call insertNodes to do the dirty work
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
            // checks if file name is valid after --help is caught... then calls printHelp to show a list of commands
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
        // otherwisem return that their flag was invalid
        else {
            cout << "Incorrect flag. Try again." << endl;
            return;
        }
    }
    // if there is only one argument then they must have only input the file name or --help
    else if( argl == 2 ) {
        string flag = args[ 1 ];
        // if they input help, printHelp
        if( flag == "--help" )
            printHelp();
        // otherwise, check if its a valid file and insertNodes if it is
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
    // lastly, they did something completely wrong... ask them to try again
    else
        cout << "Invalid input format. \nTry './ZIP --help' for running help." << endl;
}

void printHelp( ) {
    // prints the help file given to us in the directory
    ifstream helpFile;
    string curr;
    helpFile.open( "help" );

    while( getline( helpFile, curr ) ) {
        cout << curr << endl;
    }
    helpFile.close();
}

void insertNodes( string fileName, int Letters[ ], HuffmanTree tree, string flag )
{
	char ch;

    // initialize an array of size 126 to hold all ascii values
	for ( char ch = char( 0 );  ch <= char( 126 );  ch++ )
		Letters[ ch ] = 0;

	ifstream infile;
    infile.open( fileName );
    
    char curr;
    infile.get( curr );
    // gets weight of each letter in the alphabet within the input file
    while( infile ) {
        Letters[ curr ]++;
        infile.get( curr );
    }
    infile.close();

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
    // create a new file name that is the original plus .zip
	string newFile = fileName + ".zip";
	ofstream outFile( newFile );
    string encoded = "";
    float bitsB = 0;
    float bitsA = 0;

    ifstream infile;
    infile.open( fileName );

    // number of chars is inverse of 2c - 1 (numNodes)
    int numChar = ( tree.numNodes() + 1 ) / 2;
    // append the number of characters to the top of the output file
    outFile << numChar << endl;

    // if the character is in the file and array, get the ascii value and encoding of it and and append it to the output file
    for( char ch = char( 0 ); ch <= char( 126 ); ch++ )
        if( Letters[ ch ] != 0 ) 
            outFile << int( ch ) << " " << tree.GetCode( ch ) << endl;

    // for each character in the original file, get its encoding then append it to the overall encoded data string
    char ch;
    infile.get( ch );
    while( infile ) {
        // bits increase by one per each character
        bitsB++;
        encoded += tree.GetCode( ch );
        infile.get( ch );
    }
    infile.close();

    // encoded bit length is just length of the encoded string
    bitsA = encoded.length();

    // add the encoded string to the end of the output file
    outFile << encoded;
	outFile.close();

    // calculate the bit loss and print it out
    double percentage = (1 - (bitsA / (bitsB * 8))) * 100;
    cout << "File Successfully Compressed to " << bitsA << " Bits (";
    printf( "%.2f", percentage);
    cout << "% Less)." << endl;
}