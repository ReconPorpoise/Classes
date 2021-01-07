------------------------------------------------------------------------------------------------------------------------------------

# Ronald Karamuca                                                                 

# Project 1: Bingo!

------------------------------------------------------------------------------------------------------------------------------------

The objective of this project is to take a set of numbers from an input file and add them to a bingo board. 
Then, we must generate "random" numbers that will act as called numbers in a real bingo game. 

------------------------------------------------------------------------------------------------------------------------------------

Sample in/output:

Sample in:

Bingo.in
--------------
 1  2  3  4  5
 6  7  8  9 10
11 12 13 14 15
16 17 18 19 20
21 22 23 24 25


Sample out:
--------------
 X  2  3  4  X
 6  X  8  9  X
11 12  X 14 15
16  X  X  X 20
21 22 23 24  X

Numbers drawn: 1, 5, 7, 10, 13, 17, 18, 19, 25 

You win with a diagonal bingo!

Would you like to play again? (y/n): n

Thank you for playing!

------------------------------------------------------------------------------------------------------------------------------------

## Algorithm Breakdown:

-global variable that holds the winType (1 is horizontal, 2 is vertical, 3 is diagonal)


fillCard (fills the card, un-modified, with the file contents):
-takes parameter of int[][] card
-asks for a file name using: 
	-new Scanner(System.in)
-looks into file for numbers using:
	-new Scanner(fileName)
	-while(fileScanner.hasNextInt())
	-a for-for loop that sets the card slots to each number in row major order.


pickNums (picks numbers to be "called" for the bingo game --> what the cards are checked against for a bingo):
-uses parameter of int[][] card again
-declare a BitSet of size (75), to represent 1-75 that can be called in a bingo game.
	-set all BitSet elements to true
-while (checkForWin(card) is false):
	-generate a random number
	-if the number is still true in the BitSet:
		-set the index to false
		-set the same number to 0 in the card matrix if it exists
		-print the number and increment the numberCounter by one
	-check for a win again
-let the user know how many numbers it took for a bingo


checkForWin (checks all possible win cases for a 0-sum, if 0, there has been a bingo.)
-takes the int[][] card as parameter
-calculate the sum of each row
	-for-for loop that is each row's individual sum then if it's zero, break the loop, else, reset the sum and try the next row.
	-set winType to 1 if sum of a row is 0.
-calculate the sum of each column
	-for-for loop that is each column's individual sum. Same test-case as the rows. Looking for a zero-sum.
	-set winType to 2 if sum of a column is 0.
-calculate the sum of each diagonal
	-for-for loop that is, once again, the sum of each diagonal. Same test-cases. 
	-set winType to 3 if sum of a diagonal is 0.


playGame (culmination of all methods in the program)
-Wanting to make main "obsolete" or a one-liner. 
-Scanner in = new Scanner(System.in) for user input
-int[][] bingoCard = new int[5][5] generates a blank 5x5 bingo card.
-String random value for replay function comparison
-while loop (!userReplayChoice.toLowerCase().equals(sentinel));
	-Welcome to the bingo game
	-asks for the file name to fill the card (calls fillCard() method)
	-shows user the card (printCard())
	-call numbers to play the game (pickNums())
	-show the card with the X's based upon what numbers were called previously (printCard())
	-if (winType == 1) --> print horizontal bingo.
	-if (winType == 2) --> print vertical bingo.
	-if (winType == 3) --> pritn diagonal bingo.
	-asks if they want to play again (y/n)
-if break, thank the user for playing, else replay.
------------------------------------------------------------------------------------------------------------------------------------
	
	
