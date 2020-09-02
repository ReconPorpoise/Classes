/*
 * Ronald Karamuca
 * Project 2: Great Books Program
 * This program uses implementation of the Binary Search and Selection Sort algorithms to create a mock library catalog/database.
 */

import java.util.*;
import java.io.*;

public class LibraryCatalog
{
	// creates a private global arrayList that all methods can manipulate
	private static ArrayList<LibraryBook> books = new ArrayList<LibraryBook>();
	
	public static void main(String[] args) throws FileNotFoundException
	{
		// clears the terminal, then calls the fileUse (most of the magic) and menu methods to run the program
		clearScreen();
		fileUse();
		menu();
	}
	
	// displays .dat files, fills the arrayList with LibraryBook objects, returns how many books were sorted  
	public static void fileUse() throws FileNotFoundException
	{
		Scanner in = new Scanner(System.in);
		
		// all files in the dir (.)
		File currDir = new File(".");
		// create a list using the directory files pulled above		
		String[] fileNames = currDir.list();
		ArrayList<String> data = new ArrayList<String>();
	
		// finds files with .dat extension
		for (String files: fileNames)
		{
			if (files.endsWith(".dat"))
			{
				data.add(files);
			}
		}
	
		// Prompts user to enter what catalog they want to use
		System.out.println("        The Book Search Program");
		System.out.println("----------------------------------------");
		System.out.println("What file is your data stored in?");       
                System.out.println("Here are the catalogs in the directory:");  
		System.out.println();	

		// print all files that are considered usable (.dat)
		for (String dataFiles: data)
		{
			System.out.print(dataFiles + " ");
		}
	       	
		// asks for the fileName the user wants, and if it doesn't exist in the directory,
		// let them know then prompt again.
		System.out.print("\n\nEnter the file name: ");
		String fileName = in.nextLine();
		
		File catalogFile = new File(fileName);
		
		while (!catalogFile.exists())
		{
			System.out.println("\n***That file does not exist, try again.***");
			System.out.println("\nHere are the catalogs in the directory:\n");
			for (String dataFiles: data)
			{
				System.out.print(dataFiles + " " );
			}
			
			System.out.print("\n\nEnter the file name: ");
			fileName = in.nextLine();
			catalogFile = new File(fileName);
		}

		Scanner catalogScan = new Scanner(catalogFile);
		
		// adds the books to the LibraryBook arrayList by splitting the raw input at each semi-colon and using
		// the known format (t, a, c, p, g) and creating LibraryBook objects with that 
		while (catalogScan.hasNext())
		{
			String[] book = catalogScan.nextLine().split(";");
			books.add(new LibraryBook(book[0], book[1], Integer.parseInt(book[2]), Double.parseDouble(book[3]), book[4]));
		}

		clearScreen();	

		// sorts the books by calling the sortBooks method, closes the file Scanner and prompts for a continue
		sortBooks(books);					
		System.out.println("A total of " + books.size() + " books have been input and sorted by title."); 
		System.out.println("Please hit RETURN to continue...");
		catalogScan.close();
		in.nextLine();
		clearScreen();	
	}
	
	// uses a Selection Sort algorithm to sort the books 
	public static void sortBooks(ArrayList<LibraryBook> books)
	{
		// The i^th index book is considered the "smallest"
		int minIndex;
		for (int i = 0; i < books.size(); i++)
		{
			minIndex = i;
			for (int j = i + 1; j < books.size(); j++)
			{
				// if the current title is "smaller" than the current min, set the new smallest
				if (books.get(j).getTitle().compareTo(books.get(minIndex).getTitle()) < 0)
				{
					minIndex = j;
				}
			}
			// if it hasn't stopped sorting, swap the new and old smallest book
			if (minIndex != i)
			{
				LibraryBook temp = books.get(minIndex);
				books.set(minIndex, books.get(i));
				books.set(i, temp);
			}	
		}
	}
	
	// method that runs through each book in the LibraryBook arrayList
	public static void displayRecords(ArrayList<LibraryBook> books)
	{
		Scanner in = new Scanner(System.in);

		for (int i = 0; i < books.size(); i++)
		{
			// prints the info for the books starting at index 0 --> final
			printRecord(books, i);
			// creates a pause for the user to read the information, then decide if they found what they want or continue listing
			System.out.println("\nPlease hit RETURN to continue or M for Menu (all other inputs will be considered continue)...");
			
			String userIn = in.nextLine();
			if (userIn.toUpperCase().equals("M"))
			{	
				break;
			}	
			clearScreen();
		}
	}	

	// tedious formatting to print the records in a specific way
	public static void printRecord(ArrayList<LibraryBook> books, int recordIndex)
	{
		// book record position is printed at the top, followed by title, author, copyright year, price, and genre
		System.out.println("Book #" + (recordIndex + 1) + " :");         
                System.out.println("----------------------------------------");
		System.out.print(String.format("%15s", "Title :"));
		System.out.println(String.format("%25s", books.get(recordIndex).getTitle()));
		System.out.print(String.format("%15s", "Author's Name :"));
		System.out.println(String.format("%25s", books.get(recordIndex).getAuthor()));
		System.out.print(String.format("%15s", "Copyright :"));
		System.out.println(String.format("%25s", books.get(recordIndex).getCopyright()));
		System.out.print(String.format("%15s", "Price :"));
		String toPrint = String.format("%.2f", books.get(recordIndex).getPrice());
		System.out.println(String.format("%25s", toPrint));
		System.out.print(String.format("%15s", "Genre :"));
		
		// genre in the raw data is input as a one-letter string. This converts those letter codes into words to print in the record.
		String genre = "";
		switch (books.get(recordIndex).getGenre())
		{
			case "f":
				genre = "Fiction";
				break;
			case "p":
				genre = "Poetry";
				break;
			case "d":
				genre = "Drama";
				break;
		}	
		System.out.println(String.format("%25s", genre)); 
	}

	// Binary Search algorithm to find an input book as fast as possible
	public static void search(ArrayList<LibraryBook> books, String key)
	{
		int first = 0, last = books.size() - 1, middle, location;

		boolean found = false;
		
		do
		{
			middle = (first + last) / 2;
			
			// if the book (key) is found, set the loop to true (kill), if the position is lower than the current mid, 
			// make the last index to search the middle - 1, else make the starting index the middle + 1
			if (key.equals(books.get(middle).getTitle()))
			{
				found = true;
			}
			else if (key.compareTo(books.get(middle).getTitle()) < 0)
			{
				last = middle - 1;
			}
			else
			{
				first = middle + 1;
			}
		} while ((!found) && (first <= last));
		
		location = middle;
		
		if (found)
		{
			printRecord(books, location);
		}
		else 
		{
			System.out.println("Sorry. The book was not found in our database.");
		}
	}

	// menu is where all the calling and decision making is done  
	public static void menu()
	{
		Scanner in = new Scanner(System.in);
		String userIn = "0";
		
		while (!userIn.equals("3"))
		{
			System.out.println("----------------------------------------");
			System.out.println("        The Book Search Program");
                 	System.out.println("----------------------------------------");
			System.out.println("1) Display all book records");
			System.out.println("2) Search for a book by Title");
			System.out.println("3) Exit Search Program");
			System.out.println("----------------------------------------");
			System.out.print("\nPlease enter your choice > ");
			userIn = in.nextLine();
			
			// obvious, gives user options, then call the corresponding method after clearing the screen (easier on the user's eyes)	
			switch (userIn) 
			{
				case "1":
					clearScreen();
					displayRecords(books);
					clearScreen();
					break;					
				case "2":
					clearScreen();
					System.out.print("Enter the title in which you want to view > ");
					String inTitle = in.nextLine();
					clearScreen();
					search(books, inTitle);
					System.out.println("\nPress RETURN to continue...");
					in.nextLine();
					clearScreen();
					break;
				case "3":
					clearScreen();
					System.out.println("Goodbye! Thank you for using this program.");
					break;
				default:
					clearScreen();
					System.out.println("That wasn't a valid input, please try again.");
					System.out.println("\nPress RETURN to continue...");
					in.nextLine();
					clearScreen();
					break;
			}
		}
	}

	// uses unicode magic to clear the terminal screen	
	public static void clearScreen()
	{
		System.out.println("\u001b[H\u001b[2J");
	}
}	

