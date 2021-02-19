#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

string compress(string input);
string decompress(string compressed);

int main() 
{
    string myInput = "93 93 93 93 92 91 91 94 94 94 94 94 95 95 95 73 73 73 73 73 73 73";

    cout << "Original input: " << myInput << endl;

    string compressedInput = compress(myInput);
    cout << "After compression: " << compressedInput << endl;

    string uncompressed = decompress(compressedInput); 
    cout << "After decompression: " << uncompressed << endl;

}

string compress(string input) 
{
    // tokenize the string, put the tokens into a vector
    stringstream streamIn(input);
    string curr;
    vector<string> tokens;
    
    while(streamIn.good()) {
        streamIn >> curr;
        tokens.push_back(curr);
    }

    // get only one of each value in a vector
    vector<string> stripped;
    vector<string>::iterator it;
    for(int i = 0; i < tokens.size(); i++) {
        if(find(stripped.begin(), stripped.end(), tokens[i]) == stripped.end())
            stripped.push_back(tokens[i]);
    }

    // get the frequency per each unique value
    vector<int> freqs;
    for(int i = 0; i < stripped.size(); i++) 
        freqs.push_back(count(tokens.begin(), tokens.end(), stripped[i]));
        

    // create the string, in order, in a vector
    vector<string> compressed;
    for(int i = 0; i < stripped.size(); i++) {
        if(freqs[i] >= 4) {
            compressed.push_back("ff");
            compressed.push_back(stripped[i]);
            string format = string(2 - to_string(freqs[i]).length(), '0').append(to_string(freqs[i]));
            compressed.push_back(format);
        }
        else {
            for(int j = 0; j < freqs[i]; j++) {
                compressed.push_back(stripped[i]);
            }
        }
    }
    
    // join the vector into a string 
    string toReturn = "";
    for(int i = 0; i < compressed.size(); i++) {
        toReturn += compressed[i];
        if(i != compressed.size() - 1)
            toReturn += " ";
    }

    return toReturn;
}

string decompress(string compressed) 
{
    // tokenize the compressed string
    stringstream streamIn(compressed);
    string curr;

    vector<string> tokens;
    while(streamIn.good()) {
        streamIn >> curr;
        tokens.push_back(curr);
    }

    // if the current element is ff, jump 2 spaces and check how many
    // times the element 1 space forward has to be repeated
    // otherwise, just add the elements to the string
    string decompress = "";
    for(int i = 0; i < tokens.size(); i++) {
        if(tokens[i] == "ff") {
            for(int j = 0; j < stoi(tokens[i + 2]); j++) {
                decompress += tokens[i + 1];
                decompress += " ";
            }
            i += 2;
        }
        else {
            decompress += tokens[i];
            decompress += " ";
        }
    }

    return decompress;
}