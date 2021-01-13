#include <iostream>
#include <fstream>
using namespace std;
void printLines(string file, int nLines);

int main(int argc, char *argv[])
{
	// get the two arguments (number of lines they want and file name) from user
	string numLinesS = argv[1];
	string filename = argv[2];

	// remove the '-' from the line number argument
	numLinesS = numLinesS.substr(1, numLinesS.length());
	int numLines = stoi(numLinesS);

	printLines(filename, numLines);	
	return 0;
}

void printLines(string file, int nLines)
{
	// create the file stream with input mode
	fstream infile(file.c_str(), ios::in);
	// counter for '\n' and temp charater for iteration
	int eolCount = 0;
	char curr;

	// start at the end of the file...
	infile.seekg(0, ios::end);
	// while we have yet to find 'n' number of newline chars...
	while(eolCount <= nLines) {
		// go back one position
		infile.seekg(-1, ios::cur);
		// get the character at that position
		curr = infile.peek();
		// if it's a newline, increment the counter
		if(curr == '\n')
			eolCount++;	
	}
	// start getting chars from the position + 1 (remove '\n' from output) of seekg until EoF
	infile.seekg(1, ios::cur);
	while(infile.get(curr)) {
		cout << curr;
	}
	infile.clear();
	infile.close();
	
}
