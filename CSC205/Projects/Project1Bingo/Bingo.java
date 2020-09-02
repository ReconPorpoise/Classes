/*
 * Ronald Karamuca
 * Bingo game! This game allows for input of a 25 number set then plays bingo with it.
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.BitSet;
import java.util.Scanner;

public class Bingo
{
    public static int winType = 0;

    public static void main(String[] args) throws FileNotFoundException
    {
        playGame();
    }

    // Method that fills the 5x5 card with the numbers from a file
    public static void fillCard(int[][] card) throws FileNotFoundException
    {
        Scanner in = new Scanner(System.in);

        String fileName = in.nextLine();
        File inFile = new File(fileName);

        Scanner fileScan = new Scanner(inFile);

        // While there are still integers add the numbers to the card
        while (fileScan.hasNextInt())
        {
            for (int row = 0; row < card.length; row++)
            {
                for (int col = 0; col < card[row].length; col++)
                {
                    card[row][col] = fileScan.nextInt();
                }
            }
        }
        fileScan.close();
    }

    // Prints the card as "ASCII art" to show the user what the start looks like
    public static void printCard(int[][] card) //TODO: WORKS
    {
        System.out.println("\n   B    I    N    G    O");

        // Every row gets the --- separation and starts with a |
        for (int row = 0; row < card.length; row++)
        {
            System.out.println("--------------------------");
            System.out.print("| ");
            // This is each columnW
            for (int col = 0; col < card[row].length; col++) {
                //String formatting is C-like
                String numPrint = "";
                // if the element is 0 from the pickNums call, print X in their place
                // else just print the number
                if (card[row][col] == 0)
                {
                    numPrint = "X";
                }
                else
                {
                    numPrint = String.valueOf(card[row][col]);
                }
                // leaves 2 blank spaces for numbers. Single digits are right-aligned
                String toPrint = (String.format("%2s | ", numPrint));
                System.out.print(toPrint);
            }
            System.out.println();
        }
        System.out.println("--------------------------\n");
    }

    // Draws "random" numbers to match against the bingo board
    public static void pickNums(int[][] card)
    {
        // BitSet of 0-74 is made to represent the 75 possible bingo draws
        BitSet numsPicked = new BitSet(75);
        // Sets all values in the BitSet to true/1
        numsPicked.set(0, 75);

        int randomNum = 0;
        int howManyNums = 0;

        // while there is no win...
        while (checkForWin(card) == false)
        {
            // generate a random number between 1-75
            randomNum = (int) (Math.random() * 75 + 1);
            // index to match the BitSet
            int indexOfBit = randomNum - 1;

            // if the position on the random number is true in the BitSet,
            // set it to false then set the matching card number to 0.
            if (numsPicked.get(indexOfBit) == true)
            {
                numsPicked.clear(indexOfBit);

                for (int row = 0; row < card.length; row++)
                {
                    for (int col = 0; col < card[row].length; col++)
                    {
                        if (card[row][col] == randomNum)
                        {
                            card[row][col] = 0;
                        }
                    }
                }
                // Prints all the numbers that have only been drawn once then adds
                // to the count of drawn numbers
                System.out.print(randomNum + " ");
                howManyNums++;
            }
            // Check for a win --> if so, break the loop.
            checkForWin(card);
        }
        // Lets the user know how many numbers were needed
        System.out.println("\n\n" + howManyNums +" numbers picked!");
    }
	
    // Checks for win using the sums of all possible win-cases. If 0, that's a win.
    public static boolean checkForWin(int[][] card)
    {
        // Row sums:
        int rowSum = 0;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                rowSum += card[i][j];
            }

            if (rowSum == 0)
            {
                // WinType is used in playGame to determine Vertical, Horizontal, or Diagonal
                winType = 1;
                return true;
            }
            else
            {
                rowSum = 0;
            }
        }

        // Column sums:
        int colSum = 0;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                colSum += card[j][i];
            }

            if (colSum == 0)
            {
                winType = 2;
                return true;
            }
            else
            {
                colSum = 0;
            }
        }

        // Diagonal sums:
        int diag1Sum = 0; // Top left to bottom right
        int diag2Sum = 0; // Top right to bottom left
        // diag1
        for (int i = 0; i < 5; i++)
        {
            diag1Sum += card [i][i];
        }

        // diag2
        for (int i = 0; i < 5; i++)
        {
            diag2Sum += card[i][4 - i]; // first coord is (0, 4), then (1, 3), (2, 2), (3, 1), (4,0)
        }

        if (diag1Sum == 0 || diag2Sum == 0)
        {
            winType = 3;
            return true;
        }

        return false;
    }
    
    // seeks to eliminate a vebose main method. Does all the work in one method.
    public static void playGame() throws FileNotFoundException
    {
        Scanner in = new Scanner(System.in);

        int[][] bingoCard = new int[5][5];
        String userChoice = "don't get flagged";

        System.out.println("Welcome to Bingo!");

        while (!userChoice.toLowerCase().equals("n"))
        {
            System.out.println("\nYour card will be filled when you enter the file name.\nPlease enter it now:");
            fillCard(bingoCard);

            System.out.println("\nThis is your card:");
            printCard(bingoCard);

            System.out.println("Bingo numbers picked at random:");
            pickNums(bingoCard);

            System.out.println("\nThis is your card now:");
            printCard(bingoCard);

            if (winType == 1)
            {
                System.out.println("You win with a horizontal Bingo!");
            }
            else if (winType == 2)
            {
                System.out.println("You win with a vertical Bingo!");
            }
            else
            {
                System.out.println("You win with a diagonal Bingo!");
            }

            System.out.println("\nWould you like to play again? (y/n):");
            userChoice = in.nextLine();
        }
        System.out.println("Thank you for playing!");
    }
}

