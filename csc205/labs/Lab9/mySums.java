import java.lang.Math;

public class mySums
{
	public static void main(String[] args)
	{
		System.out.println(iterativeSum(4));	
		System.out.println(recurSum(4));
	}
	
	public static double iterativeSum(int n)
	{
		double sum = 0;
		for (int i = 1; i <= n; i++)
		{
			sum += (Math.pow(i, 2) + 1);
		}
		return sum;
	}

	public static double recurSum(int n)
	{
		if (n < 1)
		{
			return 0;
		}
		else 
		{
			// Set i = n (4, 3, 2, 1) then "return" the value of the Riemann sum at that value + the value below it over and over until it hits 0.
			// When n < 1, don't do anything, because the summation is supposed to stop once 1 is calculated. 
			int i = n;
			return ((Math.pow(i, 2) + 1) + recurSum(n - 1));
		}
	}
}

