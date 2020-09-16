#include <iostream>
#include "dlist.h"
using namespace std;

void HeadInsert( DList<int>& list );
void TailInsert( DList<int>& list );
void AccessItem( DList<int>& list );
void FindandMove( DList<int>& list, int item );
void Delete( DList<int>& list );
void PrintList( DList<int>& list );
void PrintLength( DList<int>& list );

int main()
{
	DList<int> list;

	HeadInsert(list);
	PrintList(list);
	Delete(list);
	PrintList(list);
	return 0;
}

void HeadInsert( DList<int>& list ) 
{
	cout << "Enter the new head: ";
	int item;
	cin >> item;
	if( list.inList( item ) ) 
		cout << "Sorry, that value is already in the list.\n" << endl;
	else
		list.insertHead(item);
}

void TailInsert( DList<int>& list )
{
	cout << "Enter the new tail: ";
	int item;
	cin >> item;
	
	if( list.inList( item ) )
		cout << "Sorry, that value is already in the list.\n" << endl;
	else 
		list.appendTail( item );
}

void AccessItem( DList<int>& list ) 
{
	cout << "Enter the value you want to access: ";
	int item;
	cin >> item;

	FindandMove( list, item );
}

void FindandMove( DList<int>& list, int item )
{
	if( list.isEmpty() ) 
		cout << "List is empty.\n";
	else if( list.inList( item ) ) {
		int newItem = item;
		list.insertHead( newItem );
		cout << "Item: " << newItem << endl;
		list.deleteItem( item );
	}
	else 
		cout << "Item not in list.\n";
}

void Delete( DList<int>& list ) 
{
	cout << "Enter item to delete: ";
	int item;
	cin >> item;

	if( list.isEmpty() ) 
		cout << "List is empty.\n";
	else if( list.inList( item ) ) {
		list.deleteItem( item );
	}
	else 
		cout << "Item not in list.\n";
}

void PrintList( DList<int>& list ) 
{
	if( list.isEmpty() ) 
		cout << "List is empty.\n";
	else 
		list.print();
}
