#include <iostream>
#include "bst.h"
using namespace std;

int main()
{
	BinarySearchTree<int> t( 0 );
	t.insert( 6 );
	t.insert( 2 );
	t.insert( 8 );
	t.insert( 1 );
	t.insert( 4 );
	t.insert( 3 );
	
	t.postOrder();

	return 0;
}
