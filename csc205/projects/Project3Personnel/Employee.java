/* Ronald Karamuca. 
 *
 * Main Employee Class of the Personnel Database Program.
 * This is where the base class is created to make most of the program work.
 */

import java.io.*;

// Class is abstract because subclasses implement the same behavior
public abstract class Employee implements java.io.Serializable
{
    private String name;
    private double hourlyWage;
    
    // Protected constructor can only be seen by subclasses
    protected Employee(String newName, double newWage) {
        name = newName;
        hourlyWage = newWage;
    }
    
    // getters and setters for names/wages
    public String getName() {
        return name;
    }

    public double getWage() {
        return hourlyWage;
    }

    public void setName(String newName) {
        name = newName;
    }

    public void setWage(double newWage) {
        hourlyWage = newWage;
    }

    // raise wage calculates the new wage by multiplying the original by 1 + (percentage in decimal form). 
    // This is to take care of the "adding back in" step all in one go
    public void raiseWage(double wage, double percentage) {
		double newWage = wage * (1 + (percentage / 100));
		setWage(newWage);
    }

    // compute pay isn't used by employee, but is very important for Salary and Hourly to implement, hence abstract
    public abstract double computePay(double wage, double hoursWorked);
}
