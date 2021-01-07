/*
 * Ronald Karamuca
 * Implementation class for the Clock program
 */

import java.util.Scanner;

public class TestClock
{
	public static void main(String[] args)
	{
		// Constructs Scanner and Clock for use. Clock is default constructor.
		Scanner in = new Scanner(System.in);
		Clock dvr = new Clock();		

		System.out.println("What time would you like to set your DVR to?");
		
		System.out.print("\nHours (0-23): ");
		int hours = in.nextInt();
		
		System.out.print("Minutes (0-59): ");
		int minutes = in.nextInt();
		
		System.out.print("Seconds (0-59): ");
		int seconds = in.nextInt();

		// Resets the Clock with the given parameters as the time
		dvr.reset(hours, minutes, seconds);
		System.out.println("\n" + dvr.toString());
		// Advances by a second
		dvr.advance();
		// Reprints after incrementing
		System.out.println("\nAdvancing the time by 1 second...\n");
		System.out.println(dvr.toString());
	}
}
