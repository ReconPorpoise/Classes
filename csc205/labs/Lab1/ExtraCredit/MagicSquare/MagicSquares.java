/*
 * Ronald Karamuca
 * A program that sees if an input matrix is a magic square
 */

import java.io.File;
import java.util.*;
import java.io.IOException;

public class MagicSquares
{
	public static void main(String[] args) throws IOException
	{
		// Initialize matrix to be filled
		int[][] matrix = new int[3][3];
		initialize(matrix);

		// Prints matrix to show that it is inputting correctly
		System.out.println("Here is the matrix:");
		for (int[] nums : matrix)
		{
			System.out.println(Arrays.toString(nums));
		}
		
		// Finds the totals for the rows
		int row1 = matrix[0][0] + matrix[0][1] + matrix[0][2];
		int row2 = matrix[1][0] + matrix[1][1] + matrix[1][2];
		int row3 = matrix[2][0] + matrix[2][1] + matrix[2][2];
		
		// Finds the totals for the columns 
		int col1 = matrix[0][0] + matrix[1][0] + matrix[2][0];
		int col2 = matrix[0][1] + matrix[1][1] + matrix[2][1];
		int col3 = matrix[0][2] + matrix[1][2] + matrix[2][2];
		
		// Finds the totals for the diagonals
		int diag1 = matrix[0][0] + matrix[1][1] + matrix[2][2];
		int diag2 = matrix[0][2] + matrix[1][1] + matrix[2][0];
		
		// Does the comparison to see if all sums are the same
		if (row1 == row2 && row1 == row3 && row1 == col1 && row1 == col2 && row1 == col3 && row1 == diag1 && row1 == diag2)
		{
			System.out.println("It is a magic square!");
		}
		else
		{
			System.out.println("It is not a magic square...");
		}
	}

	private static void initialize(int[][] matrix) throws IOException
	{
		Scanner in = new Scanner(System.in);
	
		// Asks user for the file name to pull numbers from
		System.out.println("Enter the file name:");
		String fileName = in.nextLine();

		// Creates a scanner with the file name
		Scanner inFile = new Scanner(new File(fileName));
	
		// Fills the matrix with the numbers from the files
		for (int row = 0; row < matrix.length; row++)
		{
			for (int col = 0; col < matrix[0].length; col++)
			{
				matrix[row][col] = inFile.nextInt();
			}
		}
	}
}
