public class TestEmployee
{
	public static void main(String[] args)
	{
		// Creates the hire and birth dates for an employee
		Date hireDate = new Date();
		Date birthDate = new Date(1980, 3, 8);
		
		// Constructs an employee using the parameters assigned in the Employee class	
		Employee newEmployee = new Employee("Brown", "Morris", birthDate, 40000, hireDate);
		
		System.out.println(newEmployee.toString());
	}
} 	
