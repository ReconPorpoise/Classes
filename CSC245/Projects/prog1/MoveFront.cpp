#include <iostream>
#include "dlist.h"
using namespace std;

void PrintMenu();
void HeadInsert( DList<int>& list );
void TailInsert( DList<int>& list );
void AccessItem( DList<int>& list );
void FindandMove( DList<int>& list, int item );
void Delete( DList<int>& list );
void PrintList( const DList<int>& list );
void PrintLength( const DList<int>& list );

int main()
{
	DList<int> list;
	char sel;
	
	do 
	{
		PrintMenu();
		cin >> sel;
		
		switch( toupper( sel ) )
		{
			case 'H': 
				system( "clear" );
				HeadInsert( list ); 
				break;
			case 'T': 
				system( "clear" );
				TailInsert( list );
				break;
			case 'A': 
				system( "clear" );
				AccessItem( list ); 
				break;
			case 'D': 	
				system( "clear" );
				Delete( list ); 
				break;
			case 'P': 
				system( "clear" );
				PrintList( list ); 
				break;
			case 'L': 
				system( "clear" );
				PrintLength( list ); 
				break;
			case 'Q': 
				system( "clear" );
				cout << "Program quitting...\n"; 
				break;
			default:
				system( "clear" ); 
				cout << "Incorrect input. Try again.\n";
		}
	} while( toupper( sel ) != 'Q' );
	return 0;
}

void PrintMenu() 
{
	cout << "|---------------------------------|\n";
	cout << "|------------Main Menu------------|\n";
	cout << "|---------------------------------|\n";
	cout << "|                                 |\n";
	cout << "| H: Insert item at the front     |\n";
	cout << "| T: Insert item at the end       |\n";
	cout << "| A: Access item in the list      |\n";
	cout << "| D: Delete an item in the list   |\n";
	cout << "| P: Print the whole list         |\n";
	cout << "| L: Print the list's length      |\n";
	cout << "| Q: Quit the program             |\n";
	cout << "|---------------------------------|\n";
	cout << "|                                 |\n";
	cout << "|     Please enter a command:     |\n";
}

void HeadInsert( DList<int>& list ) 
{
	cout << "Enter the new head: ";
	int item;
	cin >> item;
	if( list.inList( item ) ) 
		cout << "Sorry, that value is already in the list.\n";
	else {
		list.insertHead(item);
		cout << "Item added as head of the list.\n";
	}
}

void TailInsert( DList<int>& list )
{
	cout << "Enter the new tail: ";
	int item;
	cin >> item;
	
	if( list.inList( item ) )
		cout << "Sorry, that value is already in the list.\n";
	else 
		list.appendTail( item );
		cout << "Item added as tail of the list.\n";
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
		list.deleteItem( item );
		list.insertHead( item );
	}
	else 
		cout << "Item not in the list.\n";
}

void Delete( DList<int>& list ) 
{
	if( list.isEmpty() ) 
		cout << "List is empty.\n";
	else {
		cout << "Enter item to delete: ";
		int item;
		cin >> item;
		if( list.inList( item ) ) 
			list.deleteItem( item );
		else 
			cout << "Item not in the list.\n";
	} 
}

void PrintList( const DList<int>& list ) 
{
	if( list.isEmpty() ) 
		cout << "List is empty.\n";
	else 
		list.print();
}

void PrintLength( const DList<int>& list )
{
	if( list.isEmpty() )
		cout << "List is empty.\n";
	else
		cout << "List length: " << list.lengthIs() << endl;
}
