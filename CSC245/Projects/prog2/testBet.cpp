/*
 * Ronald Karamuca
 * Project 2: The Binary Expression Tree
 */

#include <iostream>
#include <algorithm>
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
	// Gives the menu options for the program
	printMenu();

	// Asks the user if they'd like to restart the program, then error checks input
	char answer = 'y';
	string again = "";
	
	// Runs until user decides to quit, then a deconstruct message appears
	while( answer != 'n' ) {
		cout << "\n\n\nWould you like to build another tree? (y/n): ";
		cin >> again;
		if( again.length() > 1 ) {
			while( again.length() > 1 ) {
				system( "clear" );
				cout << "Invalid input, try again." << endl;
				cout << "Would you like to build another tree? (y/n): ";
				cin >> again;
			}
		}	
		char answer = again[ 0 ];
		if( tolower( answer ) == 'y' ) {
			system("clear");
			printMenu();
		}
		if( tolower( answer ) == 'n' ) {
			system( "clear" );
			cout << "Program now dconstructing tree & exiting..." << endl;
			break;
		}
	}
	
	return 0;
}

BET postBuild( string input )
{
	// If it's an operator, add it to the BET as a Postfix operator, else add it as an operand
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
	// If it's an operator, add it to the BET as a Prefix operator, else add it as an operand
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
	// Create a stack to hold infix values, to be converted to postfix
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

	// Add surrounding parenthesis to make looping easier
	input = '(' + input;
	input += ')';

	// For each character in the expression...
	for( int i = 0; i < input.length(); i++ ) {
		curr = input[ i ];
		// push opening parenthesis to stack
		if( curr == '(' ) {
			s.push( curr );
		}
		// if it's an operator, see if it's less than or equal to the top of the stack operator.
		else if( curr == '+' || curr == '-' || curr == '*' || curr == '/' ) {
			while( precedence( s.top(), curr ) ) {
				// while it's the lowest operator, pop the operators in the stack, then push the operator to the stack.
				postfix += s.top();
				s.pop();
			}
			s.push( curr );
		}
		// if you encounter a closing parenthesis, pop all symbols until you hit '(', then pop that.
		else if( curr == ')' ) {
			while( s.top() != '(' ) {
				postfix += s.top();
				s.pop();
			}
			s.pop();
		}
		// if it's an operand, just add it to the postfix expression.
		else {
			postfix += curr;
		}
	}
	return( postBuild( postfix ) );
}

bool precedence( char prevOp, char currOp )
{
	// If the current operand is of equal value to the one in the stack... return true
	if( ( prevOp == '*' || prevOp == '/' ) && ( currOp == '*' || currOp == '/'  ) ) {
		return true;
	}
	if( ( prevOp == '+' || prevOp == '-' ) && ( currOp == '+' || currOp == '-'  ) ) {
		return true;
	}
	// If the current operand is of less value than the one in the stack... return true
	if( ( prevOp == '*' || prevOp == '/' ) && ( currOp == '+' || currOp == '-'  ) ) {
		return true;
	}
	else {
		return false;
	}
}

void printMenu() 
{
	int type;
	string expression;

	cout << "---------- Building Binary Expression Trees ----------" << endl;
	cout << "      (1) Prefix      (2) Infix      (3) Postfix      " << endl;
	
	cout << "\nYour Expression Type: ";		
	cin >> type;
	cout << "Your Expression: ";			
	cin.ignore();
	getline( cin, expression );

	expression.erase( remove( expression.begin(), expression.end(), ' ' ), expression.end() );

	cout << endl;

	// Calls for the preorder, inorder, and postorder expressions to be printed based upon the user's original input.
	// This is to avoid unwanted deconstruction of the BET if it goes out of scope.
	if( type == 1 ) {
		print( preBuild( expression ) );
	}
	else if( type == 2 ) {
		print( inBuild( expression ) );
	}
	else if( type == 3 ) {
		print( postBuild( expression ) );
	}
	else {
		cout << "Invalid input." << endl;
	}
}

void print( BET tree )
{
	// Prints the converted trees in a decent format 
	cout << "Preorder Expression Produced from Tree:\n"; tree.preorder(); cout << endl;
	cout << "\nInorder Expression Produced from Tree:\n"; tree.inorder(); cout << endl;
	cout << "\nPostorder Expression Produced from Tree:\n"; tree.postorder(); cout << endl;
}	
