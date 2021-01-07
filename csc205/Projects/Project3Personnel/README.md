# Project 3: The Personnel Database Program
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
The Personnel Database Program is a piece of software that should be able to take new employees and their wages/salaries, and calculate their pay based upon their hours.
The program should also be able to raise wages of employees, print the active records to the screen, download the records to a file "employee.dat" and upload records to the array list.

To accomplish this, I will need to implement a base abstract Employee class, with a protected constructor, an HourlyEmployee class that works with hourly employees, and SalariedEmployee class that handles salary workers.

## Employee:
* protected constructor(name, wage)
* getters and setters for name and wage
* method that increases wage by a given percentage (raiseWage())
* abstract computePay method that value-returns the weekly payment

## HourlyEmployee:
* extends Employee
* constructor with name, wage that calls super(name, wage)
* computePay method implementation that calculates ot (hoursWorked - 40) * (wage * 1.5) + (wage * 40)
* toString method that returns last name, first name (spaces that equate to a total of 40 characters overall) $wage/hour


## SalariedEmployee:
* extends Employee
* constructor with name and salary that calls super(name, (salary / (52 * 40))) to make it an hourly wage (52 weeks, 40 hours each week)
* getter and setter for salary: setSalary calls setWage(newSalary / (52 * 40)) to make sure it plays well with Employee as well as redifines private salary
* computePay() needs to just return the wage * 40 because salaried employees do not get paid over time, and each week is always 40
* toString() needs to do the same as HourlyEmployee except print the salary at the end with $salary/year

**All instances of Employee are going to be stored in an ArrayList&lt;Employee&gt;(1) to be able to access all employees**

## Implementation Class (PersonnelDatabase.java):
* menu() method to make a menu of options with a switch statement to do each operation. Needs options for: n, c, r, p, d, u, q
* options n, c, and r, need to check if the Employee in the ArrayList is a SalariedEmployee or HourlyEmployee before making calls
* need DecimalFormat to make sure all wages/salaries come out as $100.00 format
* need to check for "h" or "s" in the "n" option for what type of pay the employee takes
* check for spaces preceding or following all inputs and make it case insensitive (.trim().toLowerCase())
* all classes must be Serializable to make sure they can be converted to binary and stored into a **binary file**
* repeat use of try-catch to make sure all input is valid (keep asking for input until user provides proper format)
* use ObjIn/ObjOut as reference in Utils folder for uploading/downloading user data from/to files
* make ObjIn value-returning to return an ArrayList with added elements: if the ArrayList has elements already, append new ones to the end
* implement a clearScreen() method that clears the terminal

## Data Types: 
* salary, wage, hoursWorked, and percentage increase will be in double to keep math and toString formatting uniform
* name will be in String
* name, wage, pay, etc will eventually be converted to String when printing is needed
* Employee data type will be used in ObjIn to load the ArrayList with the proper type

