/*
 * Ronald Karamuca
 * 1-13-2021
 * CSC 310 Lab 1: Back in the Saddle Again
 * Part 1: Unix tail clone
 * Uses fstream methods to iterate through a file backwards, then print
 * from the given position.
 */
#include <iostream>
#include <fstream>
using namespace std;

void printLines(string file, int nLines);

int main(int argc, char *argv[])
{
	// get the two arguments (number of lines they want and file name) from user
	string numLinesS = argv[1];
	string filename = argv[2];
	
	// check if provided file is valid
	fstream test(filename);
	if(!test) {
		cout << "Provide a valid file: '" << filename << "' does not exist." << endl;
		return -1;
	}
	test.close();

	// remove the '-' from the line number argument
	numLinesS = numLinesS.substr(1, numLinesS.length());
	int numLines = stoi(numLinesS);

	// call function to tail
	printLines(filename, numLines);	
	return 0;
}

// function with tail logic
void printLines(string file, int nLines)
{
	// create the file stream with input mode
	fstream infile(file.c_str(), ios::in);
	// counter for '\n' and temp charater for iteration
	int eolCount = 0;
	char curr;

	// start at the end of the file...
	infile.seekg(0, ios::end);
	// keep track of what byte we are at, in case we need to tail all lines
	long size = infile.tellg();
	long currSize = 0;
	// while we have yet to find 'n' number of newline chars...
	while(eolCount <= nLines) {
		currSize++;
		// go back one position
		infile.seekg(-1, ios::cur);
		// get the character at that position
		curr = infile.peek();
		// if it's a newline, increment the counter
		if(curr == '\n')
			eolCount++;
		// if we have reached the beginning of the file, set cursor to beginning and break
		if(size == currSize) {
			infile.seekg(0, ios::beg);	
			break;
		}
	}
	curr = infile.peek();
	// if the first char in the stream is a newline, move one forward
	// else, just start printing from seekg(0, ios::beg)
	// (user wanted to tail all lines)
	if(curr == '\n')
		infile.seekg(1, ios::cur);
	while(infile.get(curr)) {
		cout << curr;
	}
	// close file stream
	infile.close();
}
