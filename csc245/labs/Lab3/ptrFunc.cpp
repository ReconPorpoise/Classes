#include <iostream>
using namespace std;

bool dataIsEqual( double* ptr1, double* ptr2 );
bool addrIsEqual( double* ptr1, double* ptr2 );

int main() 
{
	cout << "-----------------------------" << endl;
	cout << "0 == false\t    1 == true" << endl;
	cout << "-----------------------------" << endl;

	// dataIsEqual is true, addrIsEqual is false
	double* ptr1 = new double;
	double* ptr2 = new double;
	*ptr1 = 21.5;
	*ptr2 = 21.5;
	cout << "*ptr1 = 21.5\t *ptr2 = 21.5" << endl;
	cout << "dataIsEqual( ptr1, ptr2 ) : " << dataIsEqual( ptr1, ptr2 ) << endl;
	cout << "addrIsEqual( ptr1, ptr2 ) : " << addrIsEqual( ptr1, ptr2 ) << endl;
	delete ptr1;
	delete ptr2;

	// ptr3 points to data's address, and so does ptr4.
	// therefore, they share the same address and value.
	double data = 15.2;
	double* ptr3 = &data;
	double* ptr4 = &data;
	cout << "-----------------------------" << endl;
	cout << "*ptr3 = &data\t*ptr4 = &data" << endl;
	cout << "dataIsEqual( ptr3, ptr4 ) : " << dataIsEqual( ptr3, ptr4 ) << endl;
	cout << "addrIsequal( ptr3, ptr4 ) : " << addrIsEqual( ptr3, ptr4 ) << endl;
	cout << "-----------------------------" << endl;
	return 0;
}

bool dataIsEqual( double* ptr1, double* ptr2 ) 
{
	if( *ptr1 == *ptr2 ) {
		return true;
	}	
	else {
		return false;
	}
}

bool addrIsEqual( double* ptr1, double* ptr2 )
{
	if( ptr1 == ptr2 ) {
		return true;
	}
	else {
		return false;
	}
}
