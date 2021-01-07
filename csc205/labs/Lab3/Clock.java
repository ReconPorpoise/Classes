/*
 * Ronald Karamuca
 * Constructor class for the Clock program. 
 */

public class Clock 
{
	private int hours, minutes, seconds;
	
	// Clock constructors. The first takes input and the second is default override if no params given.
	public Clock(int hoursIn, int minutesIn, int secondsIn)
	{
		hours = hoursIn;
		minutes = minutesIn;
		seconds = secondsIn;
	}
	
	public Clock()
	{
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
	
	// Resets the clock to all 0 if called without param. Reset to param input otherwise.
	public void reset()
	{
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
		
	public void reset(int hoursIn, int minutesIn, int secondsIn)
	{
		hours = hoursIn;
		minutes = minutesIn;
		seconds = secondsIn;
	}
	
	// Advances the clock by 1 second. If the times go over their interval, set them to 0 and increment the next up.
	public void advance()
	{
		seconds++;
		
		if (seconds > 59)
		{
			seconds = 0;
			minutes++;
		}
		if (minutes > 59)
		{
			minutes = 0;
			hours++;
		}
		if (hours > 23)
		{
			 hours = 0;
		}
	}	
	
	// Prints the time. If the time slot is only 1 digit, add a 0 in front of it, else print as is.
	public String toString()
	{
		String output  = "The time is now ";
		
		if (hours < 10)
		{
			output += ("0" + hours + ":");
		}
		else 
		{
			output += (hours + ":");		
		}

		if (minutes < 10)
		{
			output += ("0" + minutes + ":");
		}
		else
		{
			output += (minutes + ":");
		}
		
		if (seconds < 10)
		{
			output += ("0" + seconds);
		}
		else 
		{
			output += (seconds);
		}	
		
		return output;
	}
}
