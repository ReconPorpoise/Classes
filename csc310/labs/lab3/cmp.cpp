#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

int fileCheck(int argc, char** argv, int& offset);
void diff(int argc, char** argv, int flags, int offset);
string decToOct(int num);

int main(int argc, char** argv) 
{
    int offset;
    int flags = fileCheck(argc, argv, offset);
    if(flags == -1) 
        return 1;
    diff(argc, argv, flags, offset);
}

int fileCheck(int argc, char** argv, int& offset) 
{
    // check if the user included file names
    if(argc < 3) {
        cout << "Incorrect input format. Please use './myCmp [-c] [-i N] file1 file2'." << endl;
        return -1;
    }

    // check if those files are valid
    fstream test(argv[argc - 1]);
    if(!test) {
        cout << "File 1 was invalid. Please try again." << endl;
        return -1;
    }
    test.close();
    fstream test2(argv[argc - 2]);
    if(!test2) {
        cout << "File 2 was invalid. Please try again." << endl;
        return -1;
    }
    test2.close();

    // no args
    if(argc == 3) {
        return 0;
    }
    // -c arg
    else if(argc == 4) {
        if(strcmp(argv[1], "-c") == 0) 
            return 1;
        else {
            cout << "Incorrect flag. Try [-c] or [-i N]." << endl;
            return -1;
        }
    }
    // -i N arg
    else if(argc == 5) {
        if(strcmp(argv[1], "-i") == 0) {
            offset = stoi(argv[2]);
            return 2;
        }
        else {
            cout << "Incorrect flag. Try [-c] or [-i N]." << endl;
            return -1;
        }
    }
    // -i N and -c in either order
    else if(argc == 6) {
        if(strcmp(argv[1], "-c") == 0 && strcmp(argv[2], "-i") == 0 && isdigit(*argv[3])) {
            offset = stoi(argv[3]);
            return 3;
        }
        if(strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-c") == 0 && isdigit(*argv[2])) {
            offset = stoi(argv[2]);
            return 3;
        }
        else {
            cout << "Incorrect flag. Try [-c] or [-i N]." << endl;
            return -1;
        }
    }
    else {
        cout << "Incorrect flag. Try [-c] or [-i N]." << endl;
        return -1;
    }
    return 0;
}

void diff(int argc, char** argv, int flags, int offset) 
{
    // setup file pointers
    string fn1 = argv[argc - 2];
    string fn2 = argv[argc - 1];
    fstream file1(fn1.c_str(), ios::in);
    fstream file2(fn2.c_str(), ios::in);
    file1.seekg(0, ios::beg);
    file1.seekg(0, ios::beg);

    int lineNum = 1;
    int byte = 0;

    char ch;
    char ch2;
    // while the files are alive, get the values from them
    while(file1 && file2) {
        file1.get(ch);
        file2.get(ch2);
        
        byte++; 
        if(byte > offset) {
            if(ch != ch2) {
                if(flags == 0 || flags == 2) {
                    cout << fn1 << " " << fn2 << " differ: char " << byte << ", line " << lineNum << endl;
                    break;
                }
                else if(flags == 1 || flags == 3) {
                    int chI = (int)ch;
                    int ch2I = (int)ch2;
                    // convert the number to decimal then octal
                    string oct1 = decToOct(chI);
                    string oct2 = decToOct(ch2I);
                    cout << fn1 << " " << fn2 << " differ: char " << byte << ", line " << lineNum << " is " << oct1 << " " << ch << " " << oct2 << " " << ch2 << endl;
                    break;
                }
            }
        }
        if(ch == '\n') 
            lineNum++;
    }   
    if(file1.eof() && file2.eof()) 
        return;
    else if(file1.eof())
        cout << "cmp: EOF on " << fn1 << endl;
    else if(file2.eof()) 
        cout << "cmmp: EOF on " << fn2 << endl;
    
}

// convert a decimal number to octal
string decToOct(int num) 
{
    int octal[3];
    int position = 0;

    while(num != 0) {
        octal[position] = num % 8;
        num /= 8;
        position++;
    }

    char c = octal[2];
    char b = octal[1];
    char a = octal[0];

    string toReturn = to_string(c);
    toReturn += to_string(b);
    toReturn += to_string(a);
    return toReturn;
}