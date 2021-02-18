using namespace std;
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>

class File
{
   public :
       File (const File& otherFile); // deep copy constructor 
       File (const char name[], const char pmode[],
             const char size[], const char stamp[]); // constructor that takes in all variables for private
       File (); // default constructor
       File & operator = (const File& otherFile); // operator overload to assign copies to file object
       string getSize() const;
       string getName() const;
       string getPmode() const;
       string getStamp() const;
       int recordSize() const;
       void flagAsDir(); // marks as a directory not a file
       bool isADir() const; // getter for ^

   private :
       char name[81], pmode[5], size[7], stamp[16];
       bool ADir;
};
