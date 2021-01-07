#include <iostream>
#include <cstring>
using namespace std;

struct RecType
{
	int age;
	float weight;
	char gender;
};

int main()
{
	int num = 5;
	
	int* intPtr = new int;
	intPtr = NULL;
	//intPtr = &num;
	*intPtr *= 10;
	cout << "intPtr points to :\t\t\t " << *intPtr << endl;	

	RecType* recPtr = new RecType;	
	recPtr -> age = 25;
	recPtr -> weight = 190;
	recPtr -> gender = 'M';
	(*recPtr).age += 5; 
	cout << "Three Fields Pointed to by recPtr :\t " << (*recPtr).age << " " << (*recPtr).weight << " " << (*recPtr).gender << endl;
	delete recPtr;
	recPtr = NULL;	

	char* strPtr = new char[ 50 ];		
	strcpy( strPtr, "Operating Systems" );
	cout << "strPtr points to :\t\t\t " << strPtr << endl;
	int numLower = 0;
	for( int i = 0; i < strlen( strPtr ); i++ ) {
		if( islower( *( strPtr + i ) ) ) {
			numLower++;
		}
	}
	cout << "LowerCase Letters Pointed to by strPtr : " << numLower << endl;
	strPtr += 10;
	cout << "Printing strPtr after Adding 10 :\t " << strPtr << endl;
	strPtr -= 10;
	delete strPtr;

	return 0;
}
