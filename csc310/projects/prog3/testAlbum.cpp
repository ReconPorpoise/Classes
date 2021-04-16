#include <iostream>
#include <cstring>
#include <string>
#include "album.cpp"
using namespace std;

int main() {
	String upc = "12345";
	String artist = "Polyphia";
	String title = "New Levels New Devils";
	Album test(upc, artist, title);

	cout << test << endl;
	return 0;

}
