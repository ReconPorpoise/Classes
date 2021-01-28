#include <iostream>
using namespace std;

class Fruit 
{
	public:
		void Print() {
			cout << "Fruit" << endl; }
};

class Orange : public Fruit
{
	public :
		void Print() {
			cout << "Orange" << endl;}
};

class Mandarin : public Orange
{
	public :
		void Print() {
			cout << "Mandarin" << endl;}
};

int main()
{
	Mandarin *a = new Mandarin();
	Fruit *b = new Orange();
	Orange *c = new Mandarin();

	a -> Print();
	b -> Print();
	c -> Print();
	return 0;
}
