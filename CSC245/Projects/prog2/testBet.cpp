#include <iostream>
#include <string>
#include "bet.h"
using namespace std;

BET postBuild( string input, BET tree );
BET preBuild( string input, BET tree );
void printMenu();

int main() 
{
	printMenu();	

	return 0;
}

BET postBuild( string input, BET tree )
{
	for( int i = 0; i < input.length(); i++ ) {
		if( input[ i ] == '+' || input[ i ] == '-' || input[ i ] == '*' || 
			input[ i ] == '/' ) {
			tree.insertPostfixOperator( input[ i ] );
		}
		else {
			tree.insertOperand( input[ i ] );
		}
	}
	return tree;
}

void printMenu() 
{
	BET exTree = BET();
	int type;
	string expression;

	cout << "---------- Building Binary Expression Trees ----------" << endl;
	cout << "      (1) Prefix      (2) Infix      (3) Postfix      " << endl;
	
	cout << "\nYour Expression Type: ";		cin >> type;
	cout << "\nYour Expression: ";			cin >> expression;
	
	if( type == 3 ) {
		exTree = postBuild( expression, exTree );
		exTree.preorder();
	}
}

