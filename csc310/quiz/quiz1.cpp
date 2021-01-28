#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
using namespace std;

int main()
{
	char* s = new char[10];
	char* sp= s;
	string line = ""; int i, j;
	cin >> j;
	strcpy(s, "01234");
	for(i = 0;i < j; i++) {
		*s = ('1' + i%10);
		line += *s;
		s++;
	}	

	cout << "SP: " << sp << endl;
	cout << "S: " << s << endl;
	return 0;
}
