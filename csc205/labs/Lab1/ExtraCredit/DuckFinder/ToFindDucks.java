/*
 * Ronald Karamuca
 * A program that checks if file-input sentences describe an encounter with a duck
 */

import java.util.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ToFindDucks
{
	public static void main(String[] args) throws IOException
	{
		Scanner in = new Scanner(System.in);
		
		// Asks user for file name
		System.out.println("Enter the file name:");
		String fileName = in.nextLine();
		
		// Declares the file reader and buffered reader to be able to look through the file
		FileReader readFile = new FileReader(fileName);
		BufferedReader buffRead = new BufferedReader(readFile);
		
		// Declares an ArrayList to hold each sentence from the file
		ArrayList<String> inputSentences = new ArrayList<String>();
		
		// Creates a null string for comparison to start up the while loop
		String line = null;
		while((line = buffRead.readLine()) != null)
		{
			inputSentences.add(line);
		}
		buffRead.close();
		
		// Checks each sentence in the array to see if they contain "quack", "waddle" and "swim", and if they are lowercase
		for(int i = 0; i < inputSentences.size(); i++)
        	{
            		if(inputSentences.get(i).replaceAll("\\s", "").toUpperCase().contains("QUACK") && inputSentences.get(i).replaceAll("\\s", "").toUpperCase().contains("WADDLE") && inputSentences.get(i).replaceAll("\\s", "").toUpperCase().contains("SWIM"))
            		{		
                		if((inputSentences.get(i).replaceAll("\\s", "").contains("quack") && inputSentences.get(i).replaceAll("\\s", "").contains("waddle") && inputSentences.get(i).replaceAll("\\s", "").contains("swim")) && !inputSentences.get(i).contains("Swim") && !inputSentences.get(i).contains("Quack") && !inputSentences.get(i).contains("Waddle"))
                		{
                    			System.out.println("Line " + (i + 1) + " is a duckling.");
                		}
                		else
                		{
                    			System.out.println("Line "  + (i + 1) + " is a duck.");
                		}
            		}
           		else
            		{
             			System.out.println("Line " + (i + 1) + " is not a duck.");
            		}
        	}
    	}
}

