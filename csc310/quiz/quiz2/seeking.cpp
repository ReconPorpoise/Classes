#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	fstream inp("file.dat", ios::in | ios::out);
	char small, big, sev, sevthree, temp;
	int offset = 0;
	inp.seekg(699);
	for(int i = 0; i < 4; i++) {
		if(i == 0)
			inp.get(sev);	
		else if(i == 3)
			inp.get(sevthree);
		else
			inp.get(temp);
	}
	
	if(sev < sevthree) {
		small = sev;
		big = sevthree;
	}		
	else {
		small = sevthree;
		big = sev;
	}

	inp.seekg(699);
	for(int i = 0; i < 4; i++) {
		if(i == 1)
			inp << sev;
		else if(i == 2)
			inp << sevthree;		
	}

	cout << small << " " << big << endl;

	inp.close();
	return 0;
}
