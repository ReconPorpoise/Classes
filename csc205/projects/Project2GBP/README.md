Project 2: The Great Books Program Program(?)
-------------------------------------------------------------------------------------------------------------------
The goal of this project is to create a mock-library catalog/database that allows users to view, or search,
titles of books, and displays that book's Title, Author, Date of Copyright, Price, and Genre. 

The data that is used throughout the program include fileNames input by the user, and a LibraryBook object that
has a public declaraion in another class file. These, of course, are paired with the basic data types that the 
average Java developer handles with each and every day.

To solve the searching portion of the project, a Binary Search algorithm was implemented. This, of course, 
requires the data to be sorted, which was taken-care-of by a Selection Sort algorithm (more on both below).
-------------------------------------------------------------------------------------------------------------------
The first steps taken to create the project, was a layout of CRITICAL data structures and algorithms needed.
First, it was deduced that an ArrayList, containing LibraryBook objects, was to be declared as a global (private),
variable. This is because the books are needed to run the entire program (this is a library catalog program, duh).

After this, it was decided to take on the complication of getting data from a file, decided on by the user.
A Scanner object was declared to obtain a file name from the user, then create a File object from that.
The user was given a list of .dat files from the current directory, as specified in the method.

A Selection Sort algorithm was implemented to sort all that raw data, and this was done through the Title
of the book. The way a Selection Sort works, is that it runs through each number in an array, and checks
each number after it to see if there is a smaller math. It then replaces itself with the smaller number,
and takes the array spot of the smaller number. For example:

int[] list = {5, 3, 4, 1, 2};

The first pass swaps 1 and 5 --> {1, 3, 4, 5, 2}
The seconds swaps 3 and 2 --> {1, 2, 4, 5, 3}
The third swaps 3 and 4 --> {1, 2, 3, 5, 4}
The fourth swaps 5 and 4 --> {1, 2, 3, 4, 5}

A Binary Search algorithm was used to find the user's request of a book title. This works by
starting at the middle index in an array, seeing if the "key" value is below or above that, then
decides where the middle is moved to. So in an array of 5 integers, index 3 becomes the middle, 
and the check is made to see if the key is higher or lower. At that point, the first or last
index becomes the new middle, and the check is made again to see if the number is found. The 
data MUST BE sorted for this to work, which is why a Selection Sort was used first.

A menu had to be implemented for the user to decide what they wanted to do. The options given
are "Display all book entries", "Search for a book", and "Exit". The menu is built to call
all the methods that were listed above, so it can all be contained in one place. 
-------------------------------------------------------------------------------------------------------------------
(Originally written pre-building, use of past-verbs due to translation from Notepad to Linux server)

