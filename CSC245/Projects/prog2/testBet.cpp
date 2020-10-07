#include <iostream>
#include <string>
#include "bet.h"
using namespace std;

BET postBuild( string input);
BET preBuild( string input );
BET inBuild( string input );
bool precedence( char prevOp, char currOp );
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

BET inBuild( string input ) 
{
	Stack<char> s;
	string postfix = "";
	char curr;

	/*
	int lcounter = 0;
	int rcounter = 0;

	for( int i = 0; i < input.length(); i++ ) {
		if( input[ i ] == '(' )
			lcounter++;
		if( input[ i ] == ')' )
			rcounter++;
	}
	
	while( rcounter > lcounter ) {
		input = '(' + input;
		lcounter++;
	}

	while( lcounter > rcounter ) {
		input += ')';
		rcounter++;
	}
	*/

	input = '(' + input;
	input += ')';

	for( int i = 0; i < input.length(); i++ ) {
		curr = input[ i ];
		if( curr == '(' ) {
			s.push( curr );
		}
		else if( curr == '+' || curr == '-' || curr == '*' || curr == '/' ) {
			while( precedence( s.top(), curr ) ) {
				postfix += s.top();
				s.pop();
			}
			s.push( curr );
		}
		else if( curr == ')' ) {
			while( s.top() != '(' ) {
				postfix += s.top();
				s.pop();
			}
			s.pop();
		}
		else {
			postfix += curr;
		}
	}
	return( postBuild( postfix ) );
}

bool precedence( char prevOp, char currOp )
{
	if( ( prevOp == '*' || prevOp == '/' ) && ( currOp == '*' || currOp == '/'  ) ) {
		return true;
	}
	if( ( prevOp == '+' || prevOp == '-' ) && ( currOp == '+' || currOp == '-'  ) ) {
		return true;
	}
	if( ( prevOp == '*' || prevOp == '/' ) && ( currOp == '+' || currOp == '-'  ) ) {
		return true;
	}
	else {
		return false;
	}
}

void printMenu() 
{
	string again = "y";
	while( tolower( again[ 0 ] ) != 'n' ) {
		int type;
		string expression;

		cout << "---------- Building Binary Expression Trees ----------" << endl;
		cout << "      (1) Prefix      (2) Infix      (3) Postfix      " << endl;
		
		cout << "\nYour Expression Type: ";		cin >> type;
		cout << "Your Expression: ";			cin >> expression;
		cout << endl;

		if( type == 1 ) {
			print( preBuild( expression ) );
		}
		if( type == 2 ) {
			print( inBuild( expression ) );
		}
		if( type == 3 ) {
			print( postBuild( expression ) );
		}
	}
}

void print( BET tree )
{
	cout << "Preorder Expression Produced from Tree:\n"; tree.preorder(); cout << endl;
	cout << "Inorder Expression Produced from Tree:\n"; tree.inorder(); cout << endl;
	cout << "Postorder Expression Produced from Tree:\n"; tree.postorder(); cout << endl;
}	