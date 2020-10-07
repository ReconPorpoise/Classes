#include <iostream>
#include <string>
#include "bet.h"
using namespace std;

BET postBuild( string input);
BET preBuild( string input );
void printMenu();
void print( BET tree );

int main() 
{
	printMenu();	

	return 0;
}

BET postBuild( string input )
{
	BET tree = BET();
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

BET preBuild( string input ) 
{
	BET tree = BET();
	for( int i = input.length() - 1; i >= 0; i-- ) {
		if( input[ i ] == '+' || input[ i ] == '-' || input[ i ] == '*' || 
			input[ i ] == '/' ) {
			tree.insertPrefixOperator( input[ i ] );
		}
		else {
			tree.insertOperand( input[ i ] );
		}
	}
	return tree;
}

void printMenu() 
{
	int type;
	string expression;

	cout << "---------- Building Binary Expression Trees ----------" << endl;
	cout << "      (1) Prefix      (2) Infix      (3) Postfix      " << endl;
	
	cout << "\nYour Expression Type: ";		cin >> type;
	cout << "\nYour Expression: ";			cin >> expression;
	
	if( type == 1 ) {
		print( preBuild( expression ) );
	}
	if( type == 2 ) {
		
	}
	if( type == 3 ) {
		print( postBuild( expression ) );
	}
}

void print( BET tree )
{
	cout << "Preorder: "; tree.preorder(); cout << endl;
	cout << "Inorder: "; tree.inorder(); cout << endl;
	cout << "Postorder: "; tree.postorder(); cout << endl;
}	