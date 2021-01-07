public class Employee extends Person 
{
	private double salary;
	private Date hireDate;
	
	// Constructs employee with lastName, firstName, date of birth, salary, and hire date
	// Last name, first name, and date of birth are called from the Person constructor in the parent class
	public Employee(String lName, String fName, Date dob, double salaryIn, Date hireDateIn)
	{
		super(lName, fName, dob);
		salary = salaryIn;
		hireDate = hireDateIn;
	}
	
	// Getters/Setters for salary and hireDate
	public double getSalary()
	{
		return salary;
	}

	public void setSalary(double inSalary)
	{
		salary = inSalary;
	}	

	public Date getHireDate()
	{
		return hireDate;	
	}

	public void setHireDate(Date inDate)
	{
		hireDate = inDate;
	}
	
	// Converts everything to a String to return nicely
	public String toString()
	{
		String toReturn = ("name = " + (getLastName()+ ", " + getFirstName())  + "\nsalary = " + getSalary() + "\nbirth = " + getBirthDate() + "\nhired = " + getHireDate());
		return toReturn;
	}
}
