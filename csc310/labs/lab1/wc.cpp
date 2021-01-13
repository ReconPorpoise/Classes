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
	// initialize the bool checks for user arguments
	bool lines, words, bytes;
	// initialize the filename and arguments string for checks
	string filename;
	string arguments;
	// check if the user included arguments (argc would be 3, whereas
	// it would be 2 if they only entered a file name).
	if(argc == 3 ) {	
		arguments = argv[1];
		filename = argv[2];

		// remove the '-' from the arguments
		arguments = arguments.substr(1, arguments.length());
		// checks for if the user wants line count, word count, and/or byte count
		for(int i = 0; i < arguments.length(); i++) {
			if(arguments[i] == 'l')
				lines = true;
			else if(arguments[i] == 'w')
				words = true;
			else if(arguments[i] == 'c')
				bytes = true;
		}
	}
	// if the user did not provide arguments, true all counters and grab filename
	// (this acts like wc, where all info is provided if users do not include options)
	else {
		filename = argv[1];
		lines = true;
		words = true;
		bytes = true;
	}	
	// call function for iteration of the file  
	iterate(filename, lines, words, bytes);
	return 0;
}

// main logic of the program: gets the line count, word count, and
// byte count regardless of if the user asked for it. 
// Only prints what the user wanted.
void iterate(string file, bool lines, bool words, bool bytes)
{
	// create the file stream with input mode
	fstream infile(file.c_str(), ios::in);
	// counters for line count, word count, byte count, 
	// and temp chars for current file position and prev character
	int lineCount = 0;
	int wordCount = 0;
	int byteCount = 0;
	char curr;
	char prev = '\n';

	// start at the beginning of the file...
	infile.seekg(0, ios::beg);
	// while there are still characters in the file...
	// grab the current character in the stream:
	while(infile.get(curr)) {
		// if current char is newline, but previous isn't a space character, increment word and line count
		if(curr == '\n' && prev != '\n' && prev != '\t' && prev != ' ') {
			wordCount++;
			lineCount++;
		}
		// if the curr and prev chars are newline (blank line), increment line count
		else if(curr == '\n' && prev == '\n') 
			lineCount++;
		// if the curr char is a tab, make sure the prev wasn't another space char then increment word counter
		else if(curr == '\t' && prev != ' ' && prev != '\t' && prev != '\n') 
			wordCount++;
		// if the curr char is a space, make sure the prev wasn't another space char then increment word count
		else if(curr == ' ' && prev != ' ' && prev != '\t' && prev != '\n') 
			wordCount++;

		// always increment bytes, as each char is a byte, then update prev char
		byteCount++;
		prev = curr;
	}
	// close the file stream
	infile.close();
	
	// only output what the user asked for, with the file name at the end
	string output = "";
	if(lines) {
		output += "\t";
		output += to_string(lineCount);
	}
	if(words) {
		output += "\t";
		output += to_string(wordCount);
	}	
	if(bytes) {
		output += "\t";
		output += to_string(byteCount);
	}
	output += " ";
	output += file;
	cout << output << endl;
} 
