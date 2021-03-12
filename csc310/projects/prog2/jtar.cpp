#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include "file.h"
using namespace std;
namespace fs = std::filesystem;

int argCheck(int argc, char** argv);
File getInfo(char* filename); 
void compressFiles(int argc, char** argv);

int main(int argc, char** argv)
{
    int code = argCheck(argc, argv);
    if(code == -1) {
        return 1;
    }
    return 0;
}

// checks the command-line arguments for validity
int argCheck(int argc, char** argv)
{
    if(argc == 2) {
        if(argv[1] == "--help") {
            cout << "<jtar -cf tarfile file1 dir1...> allows you to make a tar file named <tarfile> including the files given as arguments." << endl; 
            cout << "<jtar -tf tarfile> lists all the files and directories that are in the tar file." << endl;
            cout << "<jtar -xf tarfile> decompresses the <tarfile> back into its original files and directories." << endl;
            return 1;
        }
        else {
            cout << "Incorrect arguments... try <jtar --help>" << endl;
            return -1;
        }
    }
    else if(argc == 3) {
        if(argv[1] == "-tf") {
            // if(argv[2] is valid)
                // call -tf
            return 1;
        }
        else if(argv[1] == "-xf") {
            // if(argv[2] is valid)
                // call -xf
            return 1;
        }
        else {
            cout << "Incorrect arguments... try <jtar --help>" << endl;
            return -1;
        }
    }
    else if(argc > 3) {
        if(argv[1] == "-cf") {
            // call -cf which will check all files
            return 1;
        }
        else {
            cout << "Incorrect arguments... try <jtar -- help>" << endl;
            return -1;
        }
    }
    else {
        cout << "Incorrect arguments... try <jtar -- help>" << endl;
        return -1;
    }
}

// check if it is a file or dir, get permissions, size, and time
File getInfo(char* filename)
{
    struct stat buf;
    struct utimbuf timebuf;

    lstat (filename, &buf);
    int sizeRaw = buf.st_size;
    string size = to_string(sizeRaw);

    stringstream permissionRaw;
    permissionRaw << ((buf.st_mode & S_IRWXU) >> 6) << ((buf.st_mode & S_IRWXG) >> 3) << (buf.st_mode & S_IRWXO);
    string permission = permissionRaw.str();

    char stamp[16];
    strftime(stamp, 16, "%Y%m%d%H%M.%S", localtime(&buf.st_ctime));

    File toReturn(filename, permission.c_str(), size.c_str(), stamp);
    if (S_ISDIR(buf.st_mode))
        toReturn.flagAsDir();
    
    return toReturn;
}

// compresses files into tarfile
void compressFiles(int argc, char** argv)
{

}
