#include "huffman.h"
#include <iostream>
using namespace std;

HuffmanTree:: HuffmanTree()
	: numChars(0), built(false) {}

// pushes nodes to a vector
void HuffmanTree:: insert(char ch, int weight) {
    HNode newNode = {ch, weight, -1, -1}; 
    built = false;
    nodes.push_back(newNode);
    numChars++;
}

bool HuffmanTree:: inTree(char ch) {
    return lookUp( ch ) != -1;
}

int HuffmanTree:: GetFrequency(char ch) {
    return GetFrequency( lookUp( ch ) );
}

int HuffmanTree:: GetFrequency(int i) {
    return nodes[ i ].weight;
}

int HuffmanTree:: lookUp(char ch) {
    // if it's in the tree, then return its index
    for( int i = 0; i < numChars; i++ )
        if( nodes[ i ].ch == ch)
            return i;
    return -1;
}

string HuffmanTree:: GetCode(char ch) {
    return GetCode( lookUp( ch ) );
}

string HuffmanTree:: GetCode(int i) {
    // recursively look for the parent of each node until the character is reached
    if( nodes[ i ].parent == 0 )
        return "";
    else 
        return( GetCode( nodes[ i ].parent ) + ( char )( nodes[ i ].childType + '0' ) );
}

void HuffmanTree:: PrintTable() {
    int numT = 1;
    cout << "\n       Encoding Table for Zipping\n" << endl;
    cout << "Index\tChar\tWeight\tParent\tChildType\n" << endl;
    for( int i = 0; i < nodes.size(); i++ ) {
        if( nodes[ i ].ch == '\n' ) 
            cout << i << '\t' << "nl" << '\t' << nodes[ i ].weight << '\t' << nodes[ i ].parent << '\t' << nodes[ i ].childType << endl;
        else if( nodes[ i ].ch == ' ' ) 
            cout << i << '\t' << "sp" << '\t' << nodes[ i ].weight << '\t' << nodes[ i ].parent << '\t' << nodes[ i ].childType << endl;
        else if( nodes[ i ].ch == '\0' ) {
            if( nodes[ i ].childType == 123 ) 
                cout << i << '\t' << "T" << numT << '\t' << nodes[ i ].weight << '\t' << nodes[ i ].parent << '\t' << "N/A" << endl;
            else 
                cout << i << '\t' << "T" << numT << '\t' << nodes[ i ].weight << '\t' << nodes[ i ].parent << '\t' << nodes[ i ].childType << endl;
            numT++;
        }
        else 
            cout << i << '\t' << nodes[ i ].ch << '\t' << nodes[ i ].weight << '\t' << nodes[ i ].parent << '\t' << nodes[ i ].childType << endl;
    }
    cout << endl;
}

int HuffmanTree:: numNodes() {
    return nodes.size();
}

// builds the tree using the vector
void HuffmanTree:: build() {
    // adds all rows with space for total nodes
    for( int i = 0; i < ( 2 * numChars ) - 2; i++ ) {
        int smallest = i;
        int secondSmallest = 0;

        if( nodes[ i ].parent == -1 ) {
            // looks for the smallest node in the vector
            for( int j = 0; j < nodes.size(); j++ ) {
                if( nodes[ j ].weight < nodes[ smallest ].weight && nodes[ j ].parent == -1 ) 
                    smallest = j;
            }

            // increments secondSmallest because it will mess up if the secondSmallest is index 0
            while( secondSmallest == smallest || nodes[ secondSmallest ].parent != -1 ) {
                secondSmallest++;
            }

            // looks for secondSmallest in the vector, but the index cannot be the same as the smallest
            for( int j = 0; j < nodes.size(); j++ ) {
                if( nodes[ j ].weight < nodes[ secondSmallest ].weight && j != smallest && nodes[ j ].parent == -1 ) 
                    secondSmallest = j;
            }

            // creates the total node parent of the current two smallest frequencies
            int newWeight = nodes[ smallest ].weight + nodes[ secondSmallest ].weight;
            HNode temp = { '\0', newWeight, -1, -1 };
            nodes.push_back( temp );

            nodes[ smallest ].parent = nodes.size() - 1;
            nodes[ secondSmallest ].parent = nodes.size() - 1;

            nodes[ smallest ].childType = 0;
            nodes[ secondSmallest ].childType = 1;        
        }
    }

    nodes[ nodes.size() - 1 ].parent = 0;
    nodes[ nodes.size() - 1 ].childType = 123;
}