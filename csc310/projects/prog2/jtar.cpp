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
File getInfo(const char* filename); 
vector<File> getCwdFiles(int argc, char** argv);
vector<File> getAllFiles(vector<File> cwdFiles);
void compressFiles(int argc, char** argv);

int main(int argc, char** argv)
{
    int code = argCheck(argc, argv);
    if(code == -1) {
        return 1;
    }
    compressFiles(argc, argv);
    return 0;
}

int argCheck(int argc, char** argv)
{
    if(argc == 2) {
        if(strcmp(argv[1], "--help") == 0) {
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
        if(strcmp(argv[1], "-tf") == 0) {
            // if(argv[2] is valid)
                // call -tf
            return 1;
        }
        else if(strcmp(argv[1], "-xf") == 0) {
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
        if(strcmp(argv[1], "-cf") == 0) {
            for(int i = 3; i < argc; i++) {
                struct stat buf;
                lstat (argv[i], &buf);
                if (!S_ISDIR(buf.st_mode) && !S_ISREG(buf.st_mode)) {
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
File getInfo(const char* filename)
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
    // vector to hold file objects
    vector<File> allFiles;
    // for each file the user input, if it's a directory, get all sub-files in it
    for(int i = 0; i < cwdFiles.size(); i++) {
        if(cwdFiles[i].isADir()) {
            for(const auto& dirEntry : recursive_directory_iterator(cwdFiles[i].getName())) {
                string path = dirEntry.path();
                allFiles.push_back(getInfo(path.c_str()));
            }
        }
        // otherwise just push the file object to the vector
        else {
            allFiles.push_back(cwdFiles[i]);
        }
    }

    return allFiles;
}

// compresses files into tarfile
void compressFiles(int argc, char** argv)
{
    vector<File> fileList = getCwdFiles(argc, argv);
    vector<File> allFiles = getAllFiles(fileList);

    // create the archive file ready for output
    fstream output(argv[2], ios::out | ios::binary);

    int numEntries = allFiles.size();
    output.write((char*) &numEntries, sizeof(int));

    // for each file entry in the vector
    for(File entry: allFiles) {
        // write out its size; if it's a file, write out its content as well
        output.write((char*) &entry, sizeof(File));

        if(!entry.isADir()) {
            fstream curr(entry.getName().c_str(), ios::in);
            char* fileContent = new char[stoi(entry.getSize())];
            curr.read(fileContent, stoi(entry.getSize()));

            output.write(fileContent, stoi(entry.getSize()));

            curr.close();
            delete[] fileContent;
            fileContent = NULL;
        }
    }
    output.close(); 

}
