#include <iostream>
#include <string>
#include <stdlib.h>
#include "dlist.h"
using namespace std;

void PrintMenu();
void HeadInsert( DList<int>& list );
void TailInsert( DList<int>& list );
void SortList( DList<int>& list );
void AccessItem( DList<int>& list );
void FindandMove( DList<int>& list );
void Delete( DList<int>& list );
void PrintList( const DList<int>& list );
void PrintLength( const DList<int>& list );
void EmptyList( DList<int>& list );

int main()
{
	DList<int> list;
	string input;
	char choice;	

	system( "clear" );
	cout << "Welcome to the Move-to-Front program!\n";
	// Run-time loop
	do 
	{
		PrintMenu();
		cin >> input;
		// take input as a string, if it's not one char, ask again 
		// until the user sends in a char
		if( input.length() > 1 ) {
			while( input.length() > 1 ) {
				system( "clear" );
				cout << "Not a char, try again.\n";
				PrintMenu();
				cin >> input;
			}
		}	
		choice = input[ 0 ];
		switch( toupper( choice ) )
		{
			case 'H': system( "clear" ); HeadInsert( list ); break;
			case 'T': system( "clear" ); TailInsert( list ); break;
			case 'S': system( "clear" ); SortList( list ); break;
			case 'A': system( "clear" ); AccessItem( list ); break; 
			case 'D': system( "clear" ); Delete( list ); break;
			case 'P': system( "clear" ); PrintList( list ); break;
			case 'L': system( "clear" ); PrintLength( list ); break;
			case 'E': system( "clear" ); EmptyList( list ); break;
			case 'Q': system( "clear" ); cout << "Program quitting...\n"; break;
			default: system( "clear" ); cout << "Incorrect input. Try again.\n";
		}
	} while( toupper( choice ) != 'Q' );

	return 0;	
}

void PrintMenu() 
{
	cout << "------------Main Menu------------\n";
	cout << "|                               |\n";
	cout << "| H: Insert item at the front   |\n";
	cout << "| T: Insert item at the end     |\n";
	cout << "| S: Sort the list              |\n";
	cout << "| A: Access item in the list    |\n";
	cout << "| D: Delete an item in the list |\n";
	cout << "| P: Print the whole list       |\n";
	cout << "| L: Print the list's length    |\n";
	cout << "| E: Empty the list             |\n";
	cout << "| Q: Quit the program           |\n";
	cout << "|                               |\n";
	cout << "---------------------------------\n";
	cout << "Please enter a command: \n";
}

// Add a non-duplicate value to the front of the list
void HeadInsert( DList<int>& list ) 
{
	// asks for the item to be inserted as the head of the list
	cout << "Enter the new head: ";
	int item;
	cin >> item;
	// catch if it's a duplicate, then skip. otherwise add.
	if( list.inList( item ) ) 
		cout << "Sorry, that value is already in the list.\n";
	else {
		list.insertHead(item);
		cout << "Item added as head of the list.\n";
	}
}

// Add a non-duplicate value to the end of the list
void TailInsert( DList<int>& list )
{
	cout << "Enter the new tail: ";
	int item;
	cin >> item;
	
	// catch if it's a duplicate, then skip. otherwise add.
	if( list.inList( item ) )
		cout << "Sorry, that value is already in the list.\n";
	else {
		list.appendTail( item );
		cout << "Item added as tail of the list.\n";
	}
}

// Find the item in the list then move it to the front
void AccessItem( DList<int>& list ) 
{
	FindandMove( list );
}

// Looks for the item in the list: 
// if found, move it to the front
void FindandMove( DList<int>& list )
{
	// check for an empty list
	int item;
	if( list.isEmpty() ) {
		cout << "List is empty.\n";
		return;
	}
	// delete item from the list to avoid duplicates
	else {
		cout << "Enter the item you wish to access: ";
		cin >> item;
	}
	if( list.inList( item ) ) {
		list.deleteItem( item );
		list.insertHead( item );
		cout << "Item found and moved to front.\n";
	}
	else {
		cout << "Item is not in the list.\n";
	}
}

// Delete item in the list via deleteItem()
void Delete( DList<int>& list ) 
{
	// check for empty list
	if( list.isEmpty() ) 
		cout << "List is empty.\n";
	else {
		cout << "Enter item to delete: ";
		int item;
		cin >> item;
		// check if it's in the list to avoid duplicates
		if( list.inList( item ) ) {
			list.deleteItem( item );
			cout << "Item deleted from list.\n";		
		}
		else 
			cout << "Item not in the list.\n";
	} 
}

// Check if empty, otherwise print list contents
void PrintList( const DList<int>& list ) 
{
	if( list.isEmpty() ) 
		cout << "List is empty.\n";
	else 
		list.print();
}

// Check if empty, otherwise print list length
void PrintLength( const DList<int>& list )
{
	if( list.isEmpty() )
		cout << "List is empty.\n";
	else
		cout << "List length: " << list.lengthIs() << endl;
}

// Sorts list in ascending order
void SortList( DList<int>& list )
{
	if( list.isEmpty() )
		cout << "List is empty.\n";
	else {
		list.sortList();
		cout << "List sorted.\n";
	}
}

// Deletes all items in the list and frees memory
void EmptyList( DList<int>& list )
{
	if( list.isEmpty() )
		cout << "List is already empty.\n";
	else {
		list.makeEmpty();
		cout << "List has been emptied.\n";	
	}
}
