#include <iostream>
using namespace std;

int stot(string time);
int main() {
	cout << stot("5:05");
	return 0;
}
int stot(string time) {
	return (stoi(time.substr(0, 1)) * 60) + stoi(time.substr(2, 4));
}
