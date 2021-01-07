public class CheckingAccount extends Account
{
	private int numChecks;
	
	// Initializes balance in the parent class as well as sets the numChecks to 0
	public CheckingAccount(double initBalance)
	{
		super(initBalance);
		numChecks = 0;
	}
	
	// Writes a check for x amount and withdraws that from the total balance
	// Increments numChecks by 1 to signify a check being written
	public void writeCheck(double amount)
	{
		withdraw(amount);
		numChecks++;
	}

	public int getChecksWritten()
	{
		System.out.print("Checks written: ");
		return numChecks;
	}
}
