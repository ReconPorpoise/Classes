#include <iostream>
#include "bet.h"

using namespace std;

BET::BET()
{
    root = NULL;
}

BET::~BET()
{
    makeEmpty( root );
}

bool BET::isEmpty() const 
{
    return( root == NULL );
}

void BET::makeEmpty() 
{
    makeEmpty( root );
}

void BET::makeEmpty( BETPtr& t ) const 
{
    if( t != NULL ) {
        makeEmpty( t -> left );
        makeEmpty( t -> right );
		delete t;
		t = NULL;
    }
}

void BET::insertPrefixOperator( char token )
{
	// If you need a prefix operator, the top of the stack is the left and the second from the top is the right because
	// prefix prints then goes left all the way then right all the way. 
	BETPtr op = new BinaryNode;

	op->left = s.top();		s.pop();
	op->right = s.top();	s.pop();

	// Gets type of OPERATOR and opsymbol (unique to operators) because it is an operator
	op->info.whichType = OPERATOR;
	op->info.theContent.opsymbol = token;
	
	// all operators become root because the last operator should be the root node
	s.push( op );   
	root = op;
}

void BET::insertPostfixOperator( char token )
{
	// Postfix goes left right then print, so top needs to be the second (right) node.
    BETPtr op = new BinaryNode;
    
	op->right = s.top();	s.pop();
	op->left = s.top();		s.pop();
	
	op->info.whichType = OPERATOR;
	op->info.theContent.opsymbol = token;

	s.push( op );
	root = op;
}

void BET::insertOperand( char token )
{
	// Gets OPERAND type and variable instead of opsymbol
    BETPtr op = new BinaryNode;

	op->info.whichType = OPERAND;
	op->info.theContent.variable = token;

	// give it null children then push to stack
	op->left = NULL;
	op->right = NULL;

    s.push( op );
}

void BET::preorder() const 
{
    preorder( root );
}

void BET::preorder( BETPtr t ) const 
{
	// Print the proper union variable based upon it's type, then go left recursively then right recursively
	if( t == NULL )
		return;
	
	if( t->info.whichType == OPERAND ) 
		cout << t->info.theContent.variable << " ";
	if( t->info.whichType == OPERATOR )
		cout << t->info.theContent.opsymbol << " ";
	
	preorder( t->left );
	preorder( t->right );
}

void BET::inorder() const
{
    inorder( root );
}

void BET::inorder( BETPtr t ) const
{
	// If the left child is a null (all the way left), add an open parenthesis. Go recursively left, then print based upon the type, then go recursively right.
	// When you've gone all the way right, add a closing parenthesis
	if( t == NULL )
		return;
	
	if( t->left != NULL )
		cout << "( ";
	inorder( t->left );
	
	if( t->info.whichType == OPERAND ) 
		cout << t->info.theContent.variable << " ";
	if( t->info.whichType == OPERATOR )
		cout << t->info.theContent.opsymbol << " ";
	
	inorder( t->right );
	if( t->right != NULL )
		cout << ") ";
}

void BET::postorder() const
{
    postorder( root );
}

void BET::postorder( BETPtr t ) const
{
	// Go left recursively then right recursively, then print the proper union variable based upon it's type.
	if( t == NULL )
		return;
	
	postorder( t->left );
	postorder( t->right );
	
	if( t->info.whichType == OPERAND ) 
		cout << t->info.theContent.variable << " ";
	if( t->info.whichType == OPERATOR )
		cout << t->info.theContent.opsymbol << " ";
}