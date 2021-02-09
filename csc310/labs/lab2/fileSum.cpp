#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int sum(ifstream &file);

int main(int argc, char** argv) 
{
    // gets file from command-line-arguments
    string fileName = argv[1];
    ifstream infile (fileName, ios::in);
    if(!infile) {
        cout << "Invalid file. Please try again." << endl;
        return 1;
    }
    // pass the stream to the function
    int ans = sum(infile);

    cout << "The sum of the file is: " << to_string(ans) << endl;
    return 0;
}

int sum(ifstream &file) 
{
    // ans holds the sum and number holds the building-blocks for
    // each number (otherwise, we would be adding each indiviual int
    // e.g. 35 would be ans += 3 + 5, not ans += 35)
    int ans = 0;
    char ch;
    string number = "";

    file.seekg(0);
    while(file.get(ch))
    {
        // if it's end-of-file, break
        if(file.eof())
            break;
        // reset pointer if comma, also, check if there is a number in the 
        // string. If so, add that number to the sum.
        else if(ch == ',') {
            file.clear();
            if(number != "" && number != " ") {
                ans += stoi(number);
                number = "";
            }
        }
        // if it's a digit, add it to the string containing the current number.
        else if(isdigit(ch)) {
            number += ch;
        }
        // if it's an end-of-number character (e.g. spaces, tabs, commas, etc.),
        // add the string to the sum and empty the string
        else if((ch == ' ' || ch == '\n' || ch == ',' || ch == '\t') && number != "" && number != " ") {
            ans += stoi(number);
            number = "";
        }
        // if there is an invalid character in the file stream, return -1 
        else if(ch != ' ' && ch != '\n' && ch != ',' && ch != '\t' && !isdigit(ch))
            return -1;
    }
    file.close();

    return ans;
}