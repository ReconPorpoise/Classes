/* Ronald Karamuca
 *
 * Implementataion class for all Employee classes
 */

import java.io.*;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Scanner;

public class PersonnelDatabase implements Serializable
{
	public static ArrayList<Employee> employees = new ArrayList<Employee>(1);
	public static DecimalFormat df = new DecimalFormat("$###,###,###,###,###,###,###,###.00");		
	
	public static void main(String[] args) {
		clearScreen();
		Scanner in = new Scanner(System.in);
		System.out.println("Welcome to the Personnel Database Program!");
		System.out.println("\nPress RETURN to access the main menu...");
		in.nextLine();
		clearScreen();
		menu();
	}
	
	// main driver for the program. prints the menu with all the options and calls all methods.
	
	public static void menu() {
		String response = "";

		// Scanners for each data type to avoid Scanner issues
		Scanner in = new Scanner(System.in);
		Scanner ds = new Scanner(System.in);
		Scanner si = new Scanner(System.in);

		//.trim().toLowerCase() to strip all spaces and take any variation of the input commands
		while (!response.trim().toLowerCase().equals("q")) {
			clearScreen();
			System.out.println("----------------------------------");
            		System.out.println("| Commands: n - New employee     |");
            		System.out.println("|           c - Compute paychecks|");
            		System.out.println("|           r - Raise wages      |");
            		System.out.println("|           p - Print records    |");
            		System.out.println("|           d - Download data    |");
            		System.out.println("|           u - Upload data      |");
            		System.out.println("|           q - Quit             |");
            		System.out.println("----------------------------------");
			
			System.out.print("Enter command: ");
			response = in.nextLine();
			response = response.trim().toLowerCase();

			switch (response) {
				case "n":
					clearScreen();
					System.out.print("Enter the name of the new employee (last, first): ");
					String name = si.nextLine();
					String payType = "";
					String flag = "";
					double wage = 0;
					
					// make sure that payType is valid (h) or (s)
					while (!flag.equals("y")) {
						System.out.print("Hourly (h) or salary(s): ");
                        			payType = si.nextLine();
                        			payType = payType.trim().toLowerCase();

                        			if (payType.equals("h")) {
                            				flag = "y";
                        			}
                        			else if (payType.equals("s")) {
                            				flag = "y";
                        			}
                        			else {
                            				clearScreen();
                            				System.out.println("Input was not h or s; please try again.");
                            				System.out.println("\nPress RETURN to continue...");
							si.nextLine();
                            				clearScreen();
	                       			}					
						// if (h) make it do the hourly wage with HourlyEmployee
						if (payType.equals("h")) {
							wage = 0;
							while (true) {
								System.out.print("Enter hourly wage: ");
								try {
									wage = Double.parseDouble(si.nextLine());
									break;
								} catch (NumberFormatException ignore) {
									System.out.println("Wage was not in double form; try again.");
								}
							}
							HourlyEmployee newEmp = new HourlyEmployee(name, wage);
							employees.add(newEmp);
						}
						// if (s) make it do the salary with SalariedEmployee 
						if (payType.equals("s")) {
						        wage = 0;
							while (true) {
								System.out.print("Enter salary: ");
								try {
									wage = Double.parseDouble(si.nextLine());
									break;
								} catch (NumberFormatException ignore) {
									System.out.println("Wage was not in double form; try again.");
								}
							}
							SalariedEmployee newEmp = new SalariedEmployee(name, wage);
							employees.add(newEmp);
						}
					}	
					clearScreen();
					System.out.println("Employee added.\n\nPress RETURN to continue...");
					in.nextLine();
					break;
				case "c":
					for (int i = 0; i < employees.size(); i++) {
						// go through the ArrayList of employees and check if it's an Hourly or Salary
						if (employees.get(i) instanceof HourlyEmployee) {
							// hTemp is a temporary HourlyEmployee
							HourlyEmployee hTemp = (HourlyEmployee) employees.get(i);
							double hoursWorked = 0.00;
							while (true) {
								// Keep asking for hours if it's not in double form
								System.out.println("\nEnter the number of hours worked by " + hTemp.getName() + ": ");
								try {
									hoursWorked = Double.parseDouble(si.nextLine());
									break;
								} catch (NumberFormatException ignore) {
									System.out.println("Hours worked was not in double form; try again.");
								}
							}
							System.out.println("Pay: " + df.format(hTemp.computePay(hTemp.getWage(), hoursWorked)));
						}
						// if employee is salary then do it with Salaried.
						else if (employees.get(i) instanceof SalariedEmployee) {	
							// sTemp is a temporary SalariedEmployee
							SalariedEmployee sTemp = (SalariedEmployee) employees.get(i);
							double hoursWorked = 0.00;
							while (true) {
								System.out.print("\nEnter the number of hours worked by " + sTemp.getName() + ": ");
								try {
									hoursWorked = Double.parseDouble(si.nextLine());
									break;
								} catch (NumberFormatException ignore) {
									System.out.println("Hours worked was not in double form; try again.");
								}
							}
							System.out.println("Pay: " + df.format(sTemp.computePay(sTemp.getWage(), hoursWorked))); 
						}	
					}
					System.out.println("\nPress RETURN to continue...");
					in.nextLine();
					break;
				case "r":
					// Keeps asking for percentage increase until the user gives a double
					double increase = 0.00;
					while (true) {
						System.out.print("Enter percentage increase: ");
						try {
							increase = Double.parseDouble(si.nextLine());
							break;
						} catch (NumberFormatException ignore) {
							System.out.println("Increase percentage was not in double form; try again.");
						}
					}
					clearScreen();

					// print new wages based upon if it's Hourly or Salaried
					System.out.println("New Wages");
					System.out.println("---------");
					for (int i = 0; i < employees.size(); i++) {
						if (employees.get(i) instanceof HourlyEmployee) {
							HourlyEmployee rTemp = (HourlyEmployee) employees.get(i);
							rTemp.raiseWage(rTemp.getWage(), increase);
							System.out.println(rTemp.toString(rTemp));
						}
						else if (employees.get(i) instanceof SalariedEmployee) {
							SalariedEmployee rTemp = (SalariedEmployee) employees.get(i);
							rTemp.raiseWage(rTemp.getSalary(), increase);
							rTemp.setSalary(rTemp, rTemp.getWage());
							System.out.println(rTemp.toString(rTemp));
						}	
					}
					System.out.println("\n\nPress RETURN to continue...");
					in.nextLine();
					break;
				case "p":
					// print all employee records using .toString based upon Hourly or Salary
					clearScreen();
					System.out.println("Here are all employee records:");
					System.out.println("----------------------------------------");
					for (int i = 0; i < employees.size(); i++) {
						if (employees.get(i) instanceof HourlyEmployee) {
							HourlyEmployee pTemp = (HourlyEmployee) employees.get(i);
							System.out.println(pTemp.toString(pTemp));
						}
						else if (employees.get(i) instanceof SalariedEmployee) {
							SalariedEmployee pTemp = (SalariedEmployee) employees.get(i);
							System.out.println(pTemp.toString(pTemp));
						}
					}
					System.out.println("----------------------------------------");
					System.out.println("\nPress RETURN to continue...");
					in.nextLine();
					break;
				case "d":
					// calls the objOut for the ArrayList<Employee> to download all records to employee.dat
					clearScreen();
					System.out.println("Downloading Records...");
					objOut(employees);
					System.out.println("\nPress RETURN to continue...");
					in.nextLine();
					break;
				case "u":
					// calls the objIn for ArrayList<Employee> to upload employees from employee.dat
					clearScreen();
					System.out.println("Uploading Records...");
					objIn(employees);
					System.out.println("Employees have been added.\n\nPress RETURN to continue...");
					in.nextLine();
					break;
				case "q":
					// close all scanners and print a thank you message + a reminder
					in.close();
					ds.close();
					si.close();
					clearScreen();
					System.out.println("Thank you for using the Personnel Database Program.");
					System.out.println("\nIf you downloaded employee data, remember to check the 'employee.dat' file.");
					break;
				default:
					// if it's not a valid command, tell the user
					clearScreen();
					System.out.println("Command was not recognized; please try again.");
                   			System.out.println("\nPress RETURN to continue...");
                    			in.nextLine();
                    			clearScreen();
                    			break;	
			}	
		}
	}

	public static void objOut(ArrayList<Employee> emps) {
		// output the data to the file unless there is an IOException
		try {
			FileOutputStream fileOut = new FileOutputStream("employee.dat");
			ObjectOutputStream out = new ObjectOutputStream(fileOut); 
			for (int i = 0; i < emps.size(); i++) {
				out.writeObject(emps.get(i));
			}
			out.close();
			fileOut.close();
			System.out.println("Download successful.\n\nData was saved to 'employee.dat'.");
		} catch (IOException i) {
			i.printStackTrace();
		}
	} 

	public static ArrayList<Employee> objIn(ArrayList<Employee> emps) {
		// creates a iostream for employee.dat
		String fileName = "employee.dat";
		Employee newE = null;
		try {
			// while it has next, check if null. If not, add to the list.
			// if it catches IOException return the list as is
			FileInputStream fileIn = new FileInputStream(fileName);
			ObjectInputStream inTo = new ObjectInputStream(fileIn);
			Scanner readFile = new Scanner("employee.dat");
			while (readFile.hasNext() != false) {
				newE = (Employee) inTo.readObject();
				if (newE != null) {
					emps.add(newE);
				}
			}
			readFile.close();
			inTo.close();
		}
		catch (IOException e) {
			return emps;
		}
		catch (ClassNotFoundException e) {
			System.out.println(e.getMessage());
		}
		return emps;
	}
	
	// clears the terminal screen
	public static void clearScreen() {
		System.out.println("\u001b[H\u001b[2J");
	}
}
