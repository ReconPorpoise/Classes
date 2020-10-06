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
    if( root == NULL ) {

    }
    else {

    }    
}

void BET::insertPostfixOperator( char token )
{
    int s1 = s.top();   s.pop();
    int s2 = s.top();   s.pop();
    int result;
    if( token == '+' )
        result = s2 + s1;        
    if( token == '-' ) 
        result = s2 - s1;
    if( token == '*' )
        result = s2 * s1;
    if( token == '/' ) 
        result = s2 / s1;
    s.push( result );
}

void BET::insertOperand( char token )
{
    if( token == OPERAND ) 
        s.push( token );
}

void BET::preorder() const 
{
    
}

void BET::preorder( BETPtr t ) const 
{

}

void BET::inorder() const
{

}

void BET::inorder( BETPtr t ) const
{

}

void BET::postorder() const
{

}

void BET::postorder( BETPtr t ) const
{

}