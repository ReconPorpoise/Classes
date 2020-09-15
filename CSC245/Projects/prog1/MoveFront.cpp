#include <iostream>
#include "dlist.h"
using namespace std;

int main()
{
	DList<int> list;
	if( list.isEmpty() ) 
		cout << "Is it empty: yes\n";
	else 
		cout << "Is it empty: no\n";
	list.appendTail(10);
	list.insertHead(15);
	list.appendTail(20);
	cout << "Length: " << list.lengthIs() << endl;
	list.print();
	list.insertHead(30);
	list.appendTail(35);
	cout << "Length: " << list.lengthIs() << endl;
	list.print();
	
	cout << "Is 30 in list: " << list.inList(30) << endl;

	if( list.isEmpty() )	
		cout << "Is it empty: yes\n";
	else 
		cout << "Is it empty: no\n";
	return 0;
}
