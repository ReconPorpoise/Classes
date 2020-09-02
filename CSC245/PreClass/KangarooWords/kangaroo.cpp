#include <iostream>
#include <string>

using namespace std;

string toUpperCase( string s );

int main()
{
	int n;
	cin >> n;
	cout << "" << endl;
	
	for( int x = 0; x < n; x++ ) {
		// declare the variables then assign them with user-input cin values
		string w1;
		string w2;		
		cin >> w1;
		cin >> w2;
			
		w1 = toUpperCase( w1 );
		w2 = toUpperCase( w2 );

		// if the length for w1 is shorter than w2, kill because its not possible to be a kangaroo
		if( w1.length() < w2.length() ) {
			cout << w1 << " is not a kangaroo word for " << w2 << endl;
		}		
		else {
			int i = w1.length();
			int j = 0;
			int j2 = 0; 
			string kang = "";
			
			while( j < i ) {
				// characters can be compared via indices, strings cannot
				if( w1[ j ] == w2[ j2 ] ) {
					kang += w1[ j ];
					j += 1;
					j2 += 1;
					if( j2 == w2.length() ) {
						break;
					}
				}
				else {
					j += 1;
				}
			}
			// .compare is used to compare strings, not ==. 0 means equality.
			if( kang.compare( w2 ) == 0 ) {
				cout << w1 << " is a kangaroo word for " << w2 << endl;
			}
			else {
				cout << w1 << " is not a kangaroo word for " << w2 << endl;
			}
		}
	}

	return 0;
}

string toUpperCase( string s )
{
	// toupper only works on chars, so we change each character individually
	// then concatenate into a blank string to be returned 
	string toReturn = "";
	for( int i = 0; i < s.length(); i++ ) {
		toReturn += toupper( s[ i ] );
	}
	return toReturn;
}
