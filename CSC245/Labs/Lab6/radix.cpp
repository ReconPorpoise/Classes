#include <iostream>
#include <string>
#include <queue> 
#include <vector>
using namespace std;

int maxElemLength( const vector<int>& v );
int GetDigit( int number, int k );
vector<queue<int> > ItemsToQueues( const vector< int >& L, int k );
vector<int> QueuesToArray( vector<queue<int> >& QA, int numVals );
void RadixSort( vector<int>& L, int numDigits );
void PrintVector( const vector<int>& L ); 

int main( ) 
{
    vector<int> L;                  // to be sorted
    L.push_back( 380 );
    L.push_back( 95 );
    L.push_back( 345 );
    L.push_back( 382 );
    L.push_back( 260 );
    L.push_back( 100 );
    L.push_back( 492 );
    
    RadixSort( L, 7 );
    //PrintVector( L );
    return 0;
}

int maxElemLength( const vector<int>& v ) 
{
    int max = 0;
    string curr;
    for( int i = 0; i < v.size(); i++ ) {
        curr = to_string( v[ i ] );
        if( curr.length() > max )
            max = curr.length();
    }

    return max;
}

int GetDigit( int number, int k )
{
   for( int i = 0; i < k; i++ )
       number /= 10;

   return( number % 10 );
}

vector<queue<int> > ItemsToQueues( const vector< int >& L, int k )
{
    vector<queue<int> > buckets( 10 );

    for( int i = 0; i < L.size(); i++ ) {
        int num = GetDigit( L[ i ], k );
        buckets[ num ].push( L[ i ] );
    }

    return buckets;
}

vector<int> QueuesToArray( vector<queue<int> >& QA, int numVals ) 
{
    vector<int> array ( numVals );

    for( int i = 0; i < QA.size(); i++ ) {
        int inner = QA[ i ].size();
        for( int j = 0; j < inner; j++ ) {
            array.push_back( QA[ i ].front() );
            QA[ i ].pop();
        }
    }
    PrintVector(array);

    return array;
}

void RadixSort( vector<int>& L, int numDigits )
{
    vector<queue<int> > QA( 10 );
    for( int i = 0; i < numDigits; i++ ) {
        QA = ItemsToQueues( L, i );
        L = QueuesToArray( QA, numDigits );
    }
}

void PrintVector( const vector<int>& L ) 
{
    for( int i = 0; i < L.size(); i++ ) {
        cout << L[ i ] << endl;
    }
}