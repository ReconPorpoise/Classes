#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>
using namespace std;

bool validName(string name);

int main() {
	string dirName = "testDir";
	string fileName = "file1";

	cout << validName(dirName) << endl;
	cout << validName(fileName) << endl;

	return 0;
}

bool validName(string name) {
	struct stat buf;
	fstream test(name);
	lstat(name.c_str(), &buf);
	if(!test && !S_ISDIR(buf.st_mode))
		return 0;
	else 
		return 1;
}
