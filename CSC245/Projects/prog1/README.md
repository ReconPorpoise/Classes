# Project 1: The Move to Front Algorithm Program
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
THe Move to Front Algorithm Program is a program that is able to take user commands, in the form of chars, and do their associated functions. These functions include, but are not limited to, creating a new list head, adding a new item at the end of the list, and sorting the list. 

To accomplish modularity and reusability, templates are implemented to be data-type inclusive. Some functions need to be re-written to support certain data-types, but the overall logic works with any. DList takes the type of <ItemType> to allow string, char, int, or other to be passed to DList of NodeType without any issue. 

DList has the the attributes of length and head, which allows for modification of the list within the implementation file. NodeType has the attributes of ItemType info, NodeType<ItemType>* next and back to allow parsing, addition, and removal from the list.

##DList Functions:
* DList()
	* this is the constructor for DList objects that set length to 0 and head to null
* ~DList()
	* this is a destructor that calls makeEmpty() to deallocate the memory used by the doubly linked list
* void makeEmpty()
	* removes all items from the list and deallocates the memory used by it
* void deleteItem( ItemType item )
	* deletes the node and item information from the list 
* inList( ItemType item )
	* searches the list to check for the existence of the passed item, and returns true if it's found
* isEmpty()
	* returns true if the head is null (no information in the list) or false if the head has information in it (information in the list)
* print()
	* parses each node in the list and prints the info at each node as long as the head isn't null, and the end of the list hasn't been reached
* insertHead( ItemType item )
	* creates a node using the passed item as the information and setting the correct pointers based on if it's the first item in the list, or if the list already has existing nodes
* appendTail( ItemType item )
	* adds a node with info "item" to the end of the list, or sets it as head if it's the only item in the list
* lengthIs()
	* returns the attribute "length" from DList, which shows how many nodes are in the list
* location( ItemType item )
	* parses the list to find a node with info "item" and if it's found, return the pointer to it, else return null
* last()
	* returns the position of the tail of the list by parsing the list until tempNode -> next != NULL
* deleteLocation( NodeType<ItemType>* delPtr )
	* deletes the node and deallocates the memory at the pointer delPtr
* sortList()
	* moves all doubly-linked list info into a vector, the vector is then sorted using sort( vector.begin(), vector.end() ), the the list is parsed and each node -> info becomes the same index element in the vector

##Purpose
The purpose of the Move to the Front algorithm is to show how a doubly-linked list can be implemented in C++, and show the benefits of using pointers and passing-by-reference. The program also helps demonstrate how a doubly-linked list can help improve searching and sorting, by having all addresses in memory directly accessible, and having functions that do each task efficiently and effectively.

##Algorithm Design: Move to the Front
The way the algorithm is implemented is by breaking down each list operation into a function. The way "Move to the Front" is implemented is by checking the list for the item using "inList( item )", and then using "deleteItem( item )" then "insertHead( item )". This avoids duplicates, as well as stopping the algorithm if the item is not found. This saves time and lines of code. 

##Algorithm Design: Client File
The client file is implemented using a main menu function, to continuously show the options menu after each use, and clear the Linux terminal screen after each operation. The client file includes functions that call the implementation file, which keeps client clean and sleek, as one should not care how the functions were implemented in the background.

Obtaining user input is done by taking string input. It then checks if the string input is greater then 1, then lets the user know to enter a char. Once a char is entered, it breaks out of the loop and enters the main program loop. This loop calls the menu, then prompts user input. The input is then linked to a switch statement, then calls the correct function based on that. All of this is in a "do-while" loop until the user enters a case-insensitive 'Q'.
