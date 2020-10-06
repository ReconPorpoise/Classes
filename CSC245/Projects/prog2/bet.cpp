#include <iostream>
#include <stack>
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
    }
    t = NULL;
}

void BET::insertPrefixOperator( char token )
{
    
}

void BET::insertPostfixOperator( char token )
{
    BETPtr op = new BinaryNode;
    int s1 = s.top();   s.pop();
    int s2 = s.top();   s.pop();
    
}

void BET::insertOperand( char token )
{
    BETPtr op = new BinaryNode;
    if( root == NULL )
        root = op;

    op -> left = NULL;
    op -> right = NULL;

    s.push( op );
}

void BET::preorder() const 
{
    preorder( root );
}

void BET::preorder( BETPtr t ) const 
{

}

void BET::inorder() const
{
    inorder( root );
}

void BET::inorder( BETPtr t ) const
{

}

void BET::postorder() const
{
    postorder( root );
}

void BET::postorder( BETPtr t ) const
{

}