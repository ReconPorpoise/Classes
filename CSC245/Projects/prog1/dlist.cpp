#include <cstddef> 
#include <iostream>

using namespace std;

template<class ItemType>
struct NodeType
{
	ItemType info;
	NodeType<ItemType>*	next;
	NodeType<ItemType>*	back;
};

template <class ItemType>		
DList<ItemType>::DList()		// Class constructor
{
    length = 0;
    head = NULL;
}

template <class ItemType>
DList<ItemType>::~DList   ()		
{
	// Post: List is empty; All items have been deallocated.

}


template <class ItemType>
void DList<ItemType>::makeEmpty()
{
    	// Post: List is empty; all items have been deallocated.
	while( !isEmpty() ) {
		deleteLocation( last() );
	}
}

// WORKS
template <class ItemType>
void DList<ItemType>::deleteItem (ItemType item)	
{
	//  Pre :  item to be deleted is passed in via parameter 
        // Post :  item is deleted if it exists in list 
	deleteLocation( location( item ) );
}

// WORKS
template <class ItemType>
bool DList<ItemType>::inList (ItemType item) const
{
	//  Pre :  item to be located is passed in via parameter 
        // Post :  function returns bool value if item is found 
	NodeType<ItemType>* temp = new NodeType<ItemType>;
	temp = head;
	
	bool found = false;
	while( temp != NULL ) {
		if( temp -> info == item ) {
			found = true;
			return found;
		}
		else 
			temp = temp -> next;
	}
	return found;
}

// WORKS
template <class ItemType>
bool DList<ItemType>::isEmpty() const		
{
	// Post : function returns true if list is empty, false otherwise
	return head == NULL;	
}


// WORKS
template <class ItemType>
void DList<ItemType>::print() const	
{
	// Pre  : List is not empty 
	// Post : Items in List have been printed to screen
	NodeType<ItemType>* temp = new NodeType<ItemType>;
	temp = head;
	int counter = 1;
	if( temp == NULL ) {
		cout << "List is empty.\n";
	}	
	else {
		while( temp !=  NULL ) {
			cout << counter << ":\t" << temp -> info << "\n";
			temp = temp -> next;
			counter++;
		}
		cout << "End of the list.\n";
	}
}

// WORKS
template <class ItemType>
void DList<ItemType>::insertHead(ItemType item)	
{
	//  Pre : item to be inserted is passed in via parameter
        // Post : item is inserted at head of list;  Former first node is 
        //        linked back to this new one via double link;
        //        Length incremented;  Special case handled if list is empty 

	NodeType<ItemType>* newNode = new NodeType<ItemType>;
	newNode -> info = item;
	newNode -> back = NULL;
	
	if( head != NULL ) {
		head -> back = newNode;
		newNode -> next = head;
	}
	else {
		newNode -> next = NULL;
	}			

	head = newNode;
	length++;
}

// WORKS
template <class ItemType>
void DList<ItemType>::appendTail(ItemType item)
{
	//  Pre :  item to be inserted is passed in via parameter
        // Post :  item is added to tail of list; Former last node
        //         is linked to this new one via double link 
	NodeType<ItemType>* newNode = new NodeType<ItemType>;
	NodeType<ItemType>* tail = new NodeType<ItemType>;
	
	newNode -> info = item;
	newNode -> next = NULL;
	
	// look for tail, then set newNode as its next, and newNode's back as tail
	tail = head;
	if( tail == NULL ) {
		newNode -> back = NULL;
		head = newNode;
		length++;
	}
	else {
		while( tail -> next != NULL ) {
			tail = tail -> next;
		}
		tail -> next = newNode;
		newNode -> back = tail;
		
		length++;
	}
}

// WORKS
template <class ItemType>
int DList<ItemType>::lengthIs() const	
{
	// Post : Function returns current length of list  
	return length;
}

// WORKS
template <class ItemType>
NodeType<ItemType>* DList<ItemType>::location(ItemType item) const	
{
	//  Pre : item to be located is passed in via parameter 
        // Post : function returns address of item being searched for --
        //        if not found, NULL is returned  
	NodeType<ItemType>* temp = head;

	while( temp != NULL ) {
		if( temp -> info == item ) {
			return temp;
		}
		temp = temp -> next;
	}	
	return NULL;		
}

// WORKS
template <class ItemType>
NodeType<ItemType>* DList<ItemType>::last() const	
{
	// Post : Function returns location of current last item in list
	NodeType<ItemType>* temp = head;
	// keep jumping node to node until node -> next is NULL (end)
	while( temp -> next != NULL ) {
		temp = temp -> next;
	}	
	return temp;		
}

// WORKS
template <class ItemType>
void DList<ItemType>::deleteLocation (NodeType<ItemType>* delPtr)	
{

	//  Pre : Item to be deleted exits in list and its location
        //        is passed in via parameter
                   
	// Post : Location passed in is removed from list;  Length
        //        is decremented, and location is deallocated 

        // Special Cases Handled for Deleting Only One Item in List,
        // The Head Item of List, and the Tail Item of List
        
	// if its a size 1 list
	if( length == 1 ) {
		delete delPtr;
		delPtr = NULL;
		head = NULL;
		length--;
	}
	// if its the head
	else if( delPtr == head ) {
		head = delPtr -> next;
		head -> back = NULL;
		delete delPtr;
		delPtr = NULL;
		length--;
	}
	// if its the tail
	else if( delPtr == last() ) {
		// new tail is the prev node so point that to NULL, then point that back to the node behind it
		delPtr -> back -> next = NULL;
		delete delPtr;
		delPtr = NULL;
		length--;
	}
	// all others
	else {
		// node gets removed. it's old next now becomes it's previous node's next, and the it's old back now becomes the next node's back
		delPtr -> back -> next = delPtr -> next;
		delPtr -> next -> back = delPtr -> back;
		delete delPtr;
		delPtr = NULL;
		length--;
	}
}

