#include <iostream>
#include "BinaryHeap.h"
using namespace std;

int main() 
{
	BinaryHeap<char> PQ(50);

	for( char i = 'A'; i <= 'J'; i++ )
		PQ.insert( i );
	
	PQ.deleteMin( );

	cout << "Printing Left Subtree of the Root of Heap: ";
	PQ.printLtSubtree( );

	int height = PQ.Height( );
	cout << "\nThe Height of the Heap is: " << height << endl;
	
	char max = PQ.findMax( );
	cout << "The Maximum Value of the Heap is: " << max << endl;

	return 0;
}
