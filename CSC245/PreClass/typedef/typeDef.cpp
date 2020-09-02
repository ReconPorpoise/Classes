#include <iostream>
using namespace std;

typedef char* MyPtr;
typedef int MyArray[ 10 ];

void SwapValuePointedTo(MyPtr p1, MyPtr p2);

int main()
{
	MyPtr p1 = new char;
	MyPtr p2 = new char;

	*p1 = 'A';
	*p2 = 'B';

	SwapValuePointedTo(p1, p2);

	cout << "*p1 = " << *p1 << " *p2 = " << *p2 << endl;

	MyArray A = {5, 7, 0, -1, 3};
	return 0;
}

void SwapValuePointedTo(MyPtr p1, MyPtr p2)
{
	char temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}
