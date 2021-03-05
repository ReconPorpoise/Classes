#include <iostream>
#include <fstream> 
using namespace std;

int main()
{
	fstream index("album.ind", ios::in | ios::out);
	fstream avail("album.sta", ios::in | ios::out);
	
	// get the number of records so we know where the last one is
	char ch;
	avail.seekg(0, ios::beg);
	avail.get(ch);
	char records = ch;
	ch--;
	avail.seekg(0, ios::beg);
	avail << ch;
	
	// jump to the last record and get the offset/size
	int jumpTo = 5 + (10 * ((records - 1) - '0')) - 1;
	avail.seekg(jumpTo, ios::beg);
	string fspace, size;
	avail >> fspace >> size;
	avail.close();
	
	// get to that position in the main file
	string currSpace;
	string temp;
	index.seekg(0);
	while(index >> currSpace) {
		// get the number with the - then jump back to replace it
		if(currSpace == fspace) {
			index >> size;
			int len = index.tellg();
			index >> temp;
			string toInsert = temp.substr(1);
			toInsert = "+" + toInsert;
			index.seekg(len + (5 - size.length()), ios::beg);
			index << toInsert;
			break;
		}
	}
	return 0;  
}
