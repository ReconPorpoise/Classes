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
	// check if user only ran exe w/o filename 
	if(argc == 1) {
		cout << "Enter the command with the format: myWc [options -w -l -c] filename" << endl;
		return -1;
	}
	else if(argc > 2) {
		string op;
		for(int i = 1; i < argc; i++) {
			if(i == argc - 1) {
				filename = argv[i];
				break;
			}
			op = argv[i];
			op = op.substr(1, op.length());
			if(op == "l")
				lines = true;
			else if(op == "w")
				words = true;
			else if(op == "c")
				bytes = true;
			else {
				cout << "Incorrect option:" << endl;
				cout << "Your options are -w, -l, -c, in the format of 'myWc -w -l -c filename'" << endl;
				cout << "You can enter any of the 3 options in any order, or provide no options to get all information." << endl;
				return -1;
			}
		} 
	}
	else {
		filename = argv[1];
		lines = true;
		words = true;
		bytes = true;
	}	
	
	// test if file is valid
	fstream test(filename);
	if(!test) {
		cout << "Provide a valid file: '" << filename << "' does not exist." << endl;
		return -1;
	}
	test.close();

	// call function for iteration of the file  
	iterate(filename, lines, words, bytes);
	return 0;
}

// main logic of the program: gets line, word, and byte counts
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
