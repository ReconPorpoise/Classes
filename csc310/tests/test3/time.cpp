#include <iostream>
#include <string>
using namespace std;

int main() {
	string stime = "155:03";
	size_t found = stime.find(':');
	int time = stoi(stime.substr(0, found)) * 60;
	time += stoi(stime.substr(found+1, stime.length()));
	cout << time << endl;
}
