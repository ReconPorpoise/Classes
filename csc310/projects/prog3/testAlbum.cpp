#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include "album.h"
using namespace std;

int main() {
	Album album;
	string fileName = "polyphia.txt";
	fstream infile(fileName.c_str(), ios::in);
	
	set<Album> list;
	while(infile >> album)
		list.insert(album);

	for(Album x : list)
		cout << x << endl;

	return 0;
}
