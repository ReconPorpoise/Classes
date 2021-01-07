#include <iostream> 
#include <queue>
#include <string>
using namespace std;

void fillQueue( priority_queue<string>& q ); 
void printQueue( priority_queue<string> q );

int main()
{
	priority_queue<string> pq;
	fillQueue( pq );
	printQueue( pq );
	
	return 0;
}

void fillQueue( priority_queue<string>& q ) 
{
	q.push("Ronald");
	q.push("Bailey");
	q.push("Aaron");
	q.push("Madalyn");
	q.push("Karli");
	q.push("Gwen");
	q.push("Durham");
	q.push("John");
	q.push("Jane");
	q.push("Dora");
}

void printQueue( priority_queue<string> q )
{
	while( !q.empty() ) {
		cout << q.top() << endl;
		q.pop();
	}
}
