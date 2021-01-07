/* Ronald Karamuca
 *
 * Defines what a SalariedEmployee is and how it operates.
 */

import java.io.*;
import java.text.DecimalFormat;

public class SalariedEmployee extends Employee implements java.io.Serializable
{
    private double salary = 0.00;
    public DecimalFormat df = new DecimalFormat("###,###,###,###,###,###,###,###,###.00");

    // calls super as well as defines its own salary variable, which is unique to SalariedEmployee
    public SalariedEmployee(String name, double annualSalary) {
        super(name, (annualSalary / (52 * 40)));
        salary = annualSalary;
    }

    public double getSalary() {
        return salary;
    }
 
    // setSalary not only has to redefine salary, but also the Employee class' wage.
    // This is why we call setWage(newSalary / (52 * 40)). This converts it to an hourly wage.
    public void setSalary(Employee worker, double newSalary) {
        salary = newSalary;
        worker.setWage(newSalary / (52 * 40));
    }

    // assumes 40 hour work weeks because SalariedEmployees don't get OT
    public double computePay(double wage, double hoursWorked) {
        return (wage * 40);
    }

    // same concept as the HourlyEmployee toString, this time using getSalary for the pay
    public String toString(SalariedEmployee worker) {
        int space = worker.getName().indexOf(" ");

        String first = worker.getName().substring(space + 1, worker.getName().length());
        String last = worker.getName().substring(0, space - 1);
        String salary = "$" + df.format(worker.getSalary()) + "/year";

        String fullName = last + ", " + first;
        int numSpaces = 40 - (fullName.length() + salary.length());

        String toReturn = fullName;
        for (int i = 0; i < numSpaces; i++) {
            toReturn += " ";
        }
        toReturn += salary;

        return toReturn;
    }
}


