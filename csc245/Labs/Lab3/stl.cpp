#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

void Initialize(vector<int>& v);
void Print(vector<int> v);
void Reverse(vector<int>& v);

int main() 
{
	stack<string> s1, s2;

	s1.push("Hi there");
	s2.push("Alright bye");
	if( s1 == s2 ) {
		cout << "They are the same." << endl;
	}
	else if( s1 < s2 ) {
		cout << "s1 is less than s2." << endl;
	}
	else {
		cout << "s2 is less than s1." << endl;
	}

	vector<int> v;	

	// fill the vector and print it as is
	Initialize(v);
	cout << "\nv after initialization:\n";
	Print(v);
	
	// reverse the vector
	Reverse(v);
	cout << "\nv after reversing:\n";
	Print(v);

	// sort v then print
	sort(v.begin(), v.end());
	cout << "\nv after sorting:\n";
	Print(v);
	return 0;
}

void Initialize(vector<int>& v) 
{
	for( int i = 0; i < 5; i++) {
		int toPush;
		cin >> toPush;
		v.push_back(toPush);
	}
}

void Print(vector<int> v) 
{
	for( int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
}

void Reverse(vector<int>& v)
{
	vector<int> temp;
	for( int i = 0; i < v.size(); i++) {
		temp.push_back(v[i]);
	}
	for( int i = 0; i < v.size(); i++) {
		v[i] = temp[v.size() - 1 - i];
	}
}
