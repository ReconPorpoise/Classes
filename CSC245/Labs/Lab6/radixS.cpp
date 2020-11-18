#include <iostream>
#include <string>
#include <queue> 
#include <vector>
using namespace std;

int maxElemLength( const vector<string>& v );
void AddPadding( vector<string>& v );
char GetChar( string word, int k );
vector<queue<string> > ItemsToQueues( const vector< string >& L, int k );
vector<string> QueuesToArray( vector<queue<string> >& QA, int numVals );
void RemovePadding( vector<string>& v );
void RadixSort( vector<string>& L, int numChars );
void PrintVector( const vector<string>& L ); 

int main( ) 
{
    vector<string> L{ "zebra", "apple", "orange", "can", "candy", "a", "top", "pumpkin", "today", "parade" };  // to be sorted

    cout << "Before Sort:\n";
    PrintVector( L ); 
    RadixSort( L, maxElemLength( L ) );
    cout << "\nAfter Sort:\n";
    PrintVector( L );

    return 0;
}

int maxElemLength( const vector<string>& v )
{
    int max = 0;
    for( int i = 0; i < v.size(); i++ ) {
        if( v[ i ].length() > max )
            max = v[ i ].length();
    }

    return max;
}

void AddPadding( vector<string>& v ) {
    string spaces = "";
    for( int i = 0; i < v.size(); i++ ) {
        if( v[ i ].length() < maxElemLength( v ) ) {
            int size = v[ i ].length();
            for( int j = 0; j < maxElemLength( v ) - size; j++ ) {
                spaces += " ";
            }
        }
        v[ i ] = v[ i ] + spaces;
        spaces = "";
    }
}

char GetChar( string word, int k )
{
    k++;

    return( word[ word.length() - k ] );
}

vector<queue<string> > ItemsToQueues( const vector< string >& L, int k )
{
    vector<queue<string> > QA( 128 );

    for( int i = 0; i < L.size(); i++ ) {
        char letter = GetChar( L[ i ], k );
        QA[ letter ].push( L[ i ] );
    }

    return QA;
}
    
vector<string> QueuesToArray( vector<queue<string> >& QA, int numVals )
{
    vector<string> array ( numVals );
    int pos = 0;
    for( int i = 0; i < QA.size(); i++ ) {
        int inner = QA[ i ].size();
        for( int j = 0; j < inner; j++ ) {
            array[ pos++ ] = QA[ i ].front();
            QA[ i ].pop();
        }
    }

    return array;
}

void RemovePadding( vector<string>& v ) 
{
	for( int i = 0; i < v.size(); i++ ) {
		string curr = v[ i ];
		while( curr[ curr.length() - 1 ] == ' ' )
			curr = curr.substr( 0, curr.length() - 1 );
		v[ i ] = curr;
	}	
}

void RadixSort( vector<string>& L, int numChars )
{
    vector<queue<string> > QA( 128 );
    AddPadding( L );
    for( int i = 0; i < numChars; i++ ) {
        QA = ItemsToQueues( L, i );
        L = QueuesToArray( QA, L.size() );
    }
	RemovePadding( L );
}

void PrintVector( const vector<string>& L )
{
    for( int i = 0; i < L.size(); i++ ) {
        cout << L[ i ] << " ";
    }
    cout << "\n";
}
