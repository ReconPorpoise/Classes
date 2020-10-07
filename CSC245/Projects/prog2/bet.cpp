#include <iostream>
#include "stack.h"
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
	BETPtr op = new BinaryNode;

	op->right = s.top();	s.pop();
	op->left = s.top();		s.pop();

	op->info.whichType = OPERATOR;
	op->info.theContent.opsymbol = token;
	
	s.push( op );   
	root = op;
}

void BET::insertPostfixOperator( char token )
{
    BETPtr op = new BinaryNode;
    
	op->left = s.top();		s.pop();
	op->right = s.top();	s.pop();
	
	op->info.whichType = OPERATOR;
	op->info.theContent.opsymbol = token;

	s.push( op );
	root = op;
}

void BET::insertOperand( char token )
{
    BETPtr op = new BinaryNode;
	
	op->left = NULL;
	op->right = NULL;

	op->info.whichType = OPERAND;
	op->info.theContent.variable = token;

    s.push( op );
}

void BET::preorder() const 
{
    preorder( root );
}

void BET::preorder( BETPtr t ) const 
{
	if( t == NULL )
		return;
	
	if( t->info.whichType == OPERAND ) 
		cout << t->info.theContent.variable << endl;
	if( t->info.whichType == OPERATOR )
		cout << t->info.theContent.opsymbol;
	
	preorder( t->left );
	preorder( t->right );
}

void BET::inorder() const
{
    inorder( root );
}

void BET::inorder( BETPtr t ) const
{
	if( t == NULL )
		return;
	
	inorder( t->left );
	
	if( t->info.whichType == OPERAND ) 
		cout << t->info.theContent.variable << endl;
	if( t->info.whichType == OPERATOR )
		cout << t->info.theContent.opsymbol;
	
	inorder( t->right );
}

void BET::postorder() const
{
    postorder( root );
}

void BET::postorder( BETPtr t ) const
{
	if( t == NULL )
		return;

	postorder( t->left );
	postorder( t->right );
	
	if( t->info.whichType == OPERAND ) 
		cout << t->info.theContent.variable << endl;
	if( t->info.whichType == OPERATOR )
		cout << t->info.theContent.opsymbol;
}
