# Project 1: The Move to Front Algorithm Program
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
THe Move to Front Algorithm Program is a program that is able to take user commands, in the form of chars, and do their associated functions. These functions include, but are not limited to, creating a new list head, adding a new item at the end of the list, and sorting the list. 

To accomplish modularity and reusability, templates are implemented to be data-type inclusive. Some functions need to be re-written to support certain data-types, but the overall logic works with any. DList takes the type of <ItemType> to allow string, char, int, or other to be passed to DList of NodeType without any issue. 

DList has the the attributes of length and head, which allows for modification of the list within the implementation file. NodeType has the attributes of ItemType info, NodeType<ItemType>* next and back to allow parsing, addition, and removal from the list.
