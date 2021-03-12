#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include <vector>
#include "file.h"
using namespace std;
using recursive_directory_iterator = filesystem::recursive_directory_iterator;

int argCheck(int argc, char** argv);
File getInfo(char* filename); 
vector<File> getCwdFiles(int argc, char** argv);
vector<File> getAllFiles(vector<File> cwdFiles);
void compressFiles(int argc, char** argv);

int main(int argc, char** argv)
{
    int code = argCheck(argc, argv);
    if(code == -1) {
        return 1;
    }
    return 0;
}

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
            for(int i = 3; i < argc; i++) {
                fstream test(argv[i]);
                if(!test) {
                    cout << "Invalid file... try again." << endl;
                    return -1;
                }
                // call -cf function
            }
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
    // create a buffer with the info from linux stat command
    struct stat buf;
    struct utimbuf timebuf;

    // format the size to a string
    lstat (filename, &buf);
    int sizeRaw = buf.st_size;
    string size = to_string(sizeRaw);

    // format the permission bits to a string
    stringstream permissionRaw;
    permissionRaw << ((buf.st_mode & S_IRWXU) >> 6) << ((buf.st_mode & S_IRWXG) >> 3) << (buf.st_mode & S_IRWXO);
    string permission = permissionRaw.str();

    // format and save the timestamp for the file
    char stamp[16];
    strftime(stamp, 16, "%Y%m%d%H%M.%S", localtime(&buf.st_ctime));

    // create File object, check if it is a directory, then return it
    File toReturn(filename, permission.c_str(), size.c_str(), stamp);
    if (S_ISDIR(buf.st_mode))
        toReturn.flagAsDir();
    
    return toReturn;
}

// get a list of all the files in the current working directory
vector<File> getCwdFiles(int argc, char** argv) 
{
    vector<File> fileList;
    for(int i = 3; i < argc; i++) {
        fileList.push_back(getInfo(argv[i]));
    }
    return fileList;
}

// get a list of all nested files
vector<File> getAllFiles(vector<File> cwdFiles)
{
    vector<File> allFiles;
    for(int i = 0; i < allFiles.size(); i++) {
        if(allFiles[i].isADir()) {
            for(const auto& dirEntry : recursive_directory_iterator(allFiles[i].getName())) {
                allFiles.push_back(getInfo(dirEntry.path()));
            }
        }
    }

    return allFiles;
}

// compresses files into tarfile
void compressFiles(int argc, char** argv)
{
    vector<File> fileList = getCwdFiles(argc, argv);
}
