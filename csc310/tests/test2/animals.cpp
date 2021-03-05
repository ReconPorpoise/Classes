#include <iostream>
#include <fstream>
using namespace std;

int main() {
	enum Animals{RODENT, CAT, DOG, BIRD, REPTILE, HORSE, BOVINE, SHEEP};
	Animals myAnimal = CAT;
	cout << sizeof(myAnimal) << endl;
	char zippedAnimal = (char) myAnimal;
	cout << sizeof(zippedAnimal) << endl;
	cout << zippedAnimal << endl;

	fstream test("aniOut");
	test << zippedAnimal;
	test.close();

	return 0;
}
