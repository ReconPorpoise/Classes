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
	
	cout << "PostOrder: " << endl;
	t.postOrder();

	int height = t.height();
	if( height == -1 ) 
		cout << "Empty tree" << endl;
	else
		cout << "\nTree Height: " << height << endl;

	int leaves = t.numLeaves();
	if( leaves == 0 )
		cout << "Empty tree" << endl;
	else
		cout << "\nNum Leaves: " << leaves << endl;

	bool balanced = t.isBalanced();
	if( balanced == false )
		cout << "\nTree is not balanced" << endl;
	else 
		cout << "\nTree is balanced" << endl;

	t.insert( 9 );
	balanced = t.isBalanced();
	if( balanced == false )
		cout << "\nTree is not balanced after inserting 9" << endl;
	else 
		cout << "\nTree is balanced after inserting 9" << endl;
	return 0;
}
