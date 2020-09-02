/*
 * Ronald Karamuca
 * A program that allows users to enter a list of numbers then learn the mean and range of that number set
 */

import java.util.*;

public class Stats
{
	private static final int MAX_SIZE = 100;
	public static void main(String[] args)
	{
        	int[] List = new int[MAX_SIZE];		
		int numItems;

        	numItems = fillUp (List);

        	System.out.println("\n\10\7" + " The range of your " +
                                   numItems + " items is :  " + 
				   range (List, numItems));

        	System.out.println("\n\10\7" + " The mean of your " + 
                                   numItems + " items is  :  " +
				   mean (List, numItems));
	}

	public static int fillUp(int[] numList)
	{
		Scanner in = new Scanner(System.in);
		
		System.out.println("Please Input Your Values (Enter a 0 to Stop): ");	
		int userIn = in.nextInt();	
		int counter = 0;		
	
		// Uses a sentinal variable to kill the loop if the user input is 0
		while (userIn != 0)
		{
			numList[counter] = userIn;
			userIn = in.nextInt();
			counter++;
		}

		return(counter);
	}
	
	public static int range(int[] numList, int listSize)
	{
		// Sets min and max to the same value just in case users only enter 1 number
		int min = numList[0];
		int max = numList[0];

		for (int i = 0; i < listSize; i++)
		{
			// if the current number is > or < max/min, set them as such
			int toCheck = numList[i];
			if (toCheck > max)
			{
				max = toCheck;
			}
			if (toCheck < min)
			{
				min = toCheck;
			}
		}

		return (max - min);
	}
	
	public static double mean(int[] numList, int listSize)
	{
		double sum = 0;
		// For all the numbers in the list, add them together and then divide by the size of said list
		for (int nums: numList)
		{
			sum += (double)nums;
		}
		double mean = sum / (double)listSize;

		return mean;
	}
}		
