/* Ronald Karamuca
 *
 * Class that defines what an HourlyEmployee is and how it operates with pay and formatting
 */
import java.io.*;
import java.text.DecimalFormat;

public class HourlyEmployee extends Employee implements java.io.Serializable
{
    public DecimalFormat df = new DecimalFormat("###,###,###,###,###,###,###,###,###.00");
   
    // calls Employees protected constructor to create the HourlyEmployee because there is nothing new
    public HourlyEmployee(String name, double wage) {
        super(name, wage);
    }

    // computes pay with overtime: if over 40 hours, calculate base pay * 40 + remainder * (wage * 1.5).
    public double computePay(double wage, double hoursWorked) {
        if (hoursWorked <= 40) {
            return (wage * hoursWorked);
        }
        else
        {
            return (((hoursWorked - 40) * (wage * 1.5)) + (40 * wage));
        }
    }
    
    // toString cuts the name and last name at the " ", then makes the last name 0, space - 1 to avoid the ","
    // it appends these two together to make one "fullName" string then calls getWage on the object to make the pay part
    // The for loop is used to calculate the number of spaces needed in between the name and pay, to create an exactly-40 character output
    public String toString(HourlyEmployee worker) {
	int space = worker.getName().indexOf(" ");
			
	String first = worker.getName().substring(space + 1, worker.getName().length());
	String last = worker.getName().substring(0, space - 1);
	String wage = "$" + df.format(worker.getWage()) + "/hour";
	String fullName = last + ", " + first;
	int numSpaces = 40 - (fullName.length() + wage.length());
		
	String toReturn = fullName;
	for (int j = 0; j < numSpaces; j++) {
		toReturn += " ";
	}
	toReturn += wage;
	
	return toReturn;
   }	
}
