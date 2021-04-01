#include <iostream>
#include <set>
#include <fstream>
using namespace std;

void matchingItems();
int main() {
	matchingItems();	

	return 0;
}

void matchingItems()
{
	fstream file1("file1.txt", ios::in);
	fstream file2("file2.txt", ios::in);
	set<string> names1;
	set<string> names2;
	char curr1;
	char curr2;
	string rec1 = "";
	string rec2 = "";
	file1.seekg(0);
	file2.seekg(0);
	while(file1.get(curr1) || file2.get(curr2)) {
		if(curr1 != '\n')
			rec1 += curr1;
		else {
			names1.insert(rec1);
			rec1 = "";
		}
		if(curr2 != '\n')
			rec2 += curr2;
		else {
			names2.insert(rec2);
			rec2 = "";
		}
	}
	set<string>::iterator i;
	set<string>::iterator j;
	set<string> smaller;
	set<string> bigger;
	if(names1.size() > names2.size()) {
		smaller = names2;
		bigger = names1;
	}
	else {
		smaller = names1;
		bigger = names2;
	}

	
	for(i = smaller.begin(); i != smaller.end(); i++) {
		j = bigger.find(*i);
		if(j != bigger.end())
			cout << *j << endl;
	}	
}
