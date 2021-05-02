#include <iostream>
#include <string>
using namespace std;

int H(char *S);
int H2(char *S);

int main() {
	char* one = "BARE";
	char* two = "BEAR";

	cout << "one H: " << H(one) << endl;
	cout << "one H2: " << H2(one) << endl;
	cout << "two H: " << H(two) << endl;
	cout << "two H2: " << H2(two) << endl;
	return 0;
}

int H(char* S) {
	int r = 1;
	int i;
	for(i = 0; i < 4; ++i)
		r = r * (int)S[i];	
	return r % 2001;
}

int H2(char* S) {
	int r = 0;
 	int i;
	for(i = 0; i < 4; ++i)
		r = 3*r + (int) S[i];
	return r % 2001;
}
