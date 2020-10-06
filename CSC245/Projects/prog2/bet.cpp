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

bool BET::isEmpty() const {
    return( root == NULL );
}

void BET::makeEmpty() {
    makeEmpty( root );
}

void BET::makeEmpty( BETPtr& t ) const {
    
}