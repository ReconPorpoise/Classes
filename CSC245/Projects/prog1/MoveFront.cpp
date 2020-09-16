#include <iostream>
#include "dlist.h"
using namespace std;

int main()
{
	DList<int> list;
	list.insertHead(10);
	list.appendTail(15);
	list.appendTail(20);
	list.appendTail(25);
	cout << "First list print:\n";
	list.print();
	
	list.deleteItem(10);
	cout << "List after head removed:\n";
	list.print();
	
	list.deleteItem(25);
	cout << "List after tail removed:\n";
	list.print();

	list.deleteItem(15);
	cout << "List after tail removed:\n";
	list.print();
	
	list.deleteItem(20);
	cout << "List after last item removed:\n";
	list.print();

	return 0;
}
