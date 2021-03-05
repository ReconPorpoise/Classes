#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int uncomp(string compressed);
int hexToDec(string hex);

int main()
{
	string compressed = "ff 93 04 92 91 91 ff 94 1a";
	cout << uncomp(compressed) << endl;

	return 0;
}

int uncomp(string compressed) {
	stringstream streamIn(compressed);
    string curr;
	int count = 0;

    vector<string> tokens;
    while(streamIn.good()) {
        streamIn >> curr;
        tokens.push_back(curr);
    }

    // if the current element is ff, jump 2 spaces and check how many
    // times the element 1 space forward has to be repeated
    // otherwise, just add the elements to the string
    for(int i = 0; i < tokens.size(); i++) {
        if(tokens[i] == "ff") {
			count += hexToDec(tokens[i + 2]);	
            i += 2;
        }
        else {
			count++;
        }
    }

    return count;	
}

int hexToDec(string hex) {
	return stoi(hex, 0, 16);
}
