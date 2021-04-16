#include <iostream>
#include <set>
#include <fstream>
#include <algorithm>
using namespace std;

void oneDose(fstream& file1, fstream& file2);

int main() {
	fstream f1("list1.txt", ios::in);
	fstream f2("list2.txt", ios::in);
	oneDose(f1, f2);
	return 0;
}

void oneDose(fstream& file1, fstream& file2) {
	set<string> names1;
	set<string> names2;
	string rec1; string rec2;
	while(!file1.eof() || !file2.eof()) {
		getline(file1, rec1);
		getline(file2, rec2);
		names1.insert(rec1);
		names2.insert(rec2);
	}
	
	set<string> diff;
	set_difference(names1.begin(), names1.end(), names2.begin(), names2.end(), inserter(diff, diff.end()));
	set_difference(names2.begin(), names2.end(), names1.begin(), names1.end(), inserter(diff, diff.end()));

	set<string>::iterator i;
	for(i = diff.begin(); i != diff.end(); i++)
		cout << *i << endl;
}
