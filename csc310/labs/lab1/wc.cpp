/*
 * Ronald Karamuca
 * 1-13-2021
 * CSC 310 Lab 1: Back in the Saddle Again
 * Part 2: Unix wc clone
 * Uses fstream methods to iterate through a file, get the number of lines,
 * words, and bytes in the file, then outputs that information to the user.
 */
#include <iostream>
#include <fstream>
using namespace std;

void iterate(string file, bool lines, bool words, bool bytes);

int main(int argc, char *argv[])
{
	// get two items from argv, the arguments and file name
	string arguments = argv[1];
	string filename = argv[2];

	// remove the '-' from the arguments
	arguments = arguments.substr(1, arguments.length());
	
	// checks for if the user wants line count, word count, and byte count
	bool lines, words, bytes;
	for(int i = 0; i < arguments.length(); i++) {
		if(arguments[i] == 'l')
			lines = true;
		else if(arguments[i] == 'w')
			words = true;
		else if(arguments[i] == 'c')
			bytes = true;
	}

	// call function 
	iterate(filename, lines, words, bytes);
	return 0;
}

void iterate(string file, bool lines, bool words, bool bytes)
{
	// create the file stream with input mode
	fstream infile(file.c_str(), ios::in);
	// counters for line count, word count, byte count, 
	// and temp char for current file position
	int lineCount = 0;
	int wordCount = 0;
	int byteCount = 0;
	char curr;

	// start at the beginning of the file...
	infile.seekg(0, ios::beg);
	// while there are still characters in the file...
	while(infile.get(curr)) {
		// get the current character and check if it's a '\n' or space:
		curr = infile.peek();
		// if new line, there must be a word before it, so add one to word
		// as well as the line counter. 
		// This is because the word before the '\n' wouldn't be counted.
		if(curr == '\n') {
			lineCount++;
			wordCount++;
		}
		// if it's a space, add one to word count
		else if(curr == ' ')
			wordCount++;
		byteCount++;
	}
	// close the file stream

	infile.close();
	// wordCount will always be 1 too high because if there is a new line,
	// we increment. This will ALWAYS cause it to be 1 too high, so decrement.
	wordCount--;
	
	string output = "";
	
} 
