#include <fstream>
#include <cctype>
#include <iostream>
using namespace std;

#include <string>
#include "stack.h" 

struct AdviceNode
{
  string QorA;      // a question or an answer
  AdviceNode * yes;   // yes branch
  AdviceNode * no;    // no branch

  AdviceNode(const string & s);  // constructor
};

AdviceNode::AdviceNode(const string & s)
: QorA(s),
  yes(NULL),
  no(NULL)
{}

void ReadTree(istream & in, AdviceNode * & T);

bool IsQuestionNode(AdviceNode * T);
// precondition:  T is not NULL
// postcondition: returns true f T points to a question node;
//                otherwise returns false

void GiveAdvice(AdviceNode * T);
// precondition: T is not NULL

bool TracePath(AdviceNode * T, const string & movie,
               Stack<string> & pathStack);
// precondition:  T is not NULL

void ShowPath(const Stack<string> & pathStack);

int main()
{
  string fname;
  cout << "\nEnter filename of advice knowledge base: ";
  cin  >> fname; cin.ignore();

  ifstream treeIn(fname.c_str());

  AdviceNode * T;
  ReadTree(treeIn, T);

  GiveAdvice(T);

  string movie;
  Stack<string> path;

  while(movie != "q"){
    cout << "\nEnter the name of a movie from tree to see path (q to quit): ";
    getline(cin, movie);
    if(movie != "q"){
      path.makeEmpty();
      TracePath(T, movie, path);
      ShowPath(path);
    }
  }

  return 0;
}

void ReadTree(istream & in, AdviceNode * & T)
{
  string QA;

  getline(in, QA);
  T = new AdviceNode(QA);
  if(QA[QA.length()-1] != '?'){
    T->yes = NULL;
    T->no  = NULL;
  }
  else{
    ReadTree(in, T->yes);
    ReadTree(in, T->no);
  }
}

bool IsQuestionNode(AdviceNode * T)
// precondition:  T is not NULL
// postcondition: returns true f T points to a question node;
//                otherwise returns false
{
  return (T->QorA[(T->QorA).length()-1] == '?');
}

void GiveAdvice(AdviceNode * T)
{
// 1)  Check to see if T is a Question Node.
// 2)  If it is, print T -> QorA and Input a 'Y' or 'N' (in any case).
//     If 'Y', recursively go left (T -> yes).  Otherwise, recursively go right.
// 3)  If the node is not a Question Node, it is a leaf and answer node.  So, just print T -> QorA.
  if( !IsQuestionNode( T ) ) {
    cout << T->QorA << endl;
  }
  else {
	cout << T->QorA << endl;
	string choice;
	getline( cin, choice );
	if( tolower( choice[ 0 ] ) == 'y' ) {
	  GiveAdvice( T->yes );
	}
	if( tolower( choice[ 0 ] ) == 'n' ) {
	  GiveAdvice( T->no );
	}
  }
}

// will recursively go yes and no until it finds the movie,
// then pushes the question, with the answer it needs, to 
// the stack.
bool TracePath(AdviceNode * T, const string & movie,
               Stack<string> & pathStack)
{
  if( T == NULL )
	return false;
  // is the path empty?
  if( pathStack.isEmpty() ) {
	// then recursively check no
	TracePath( T->no, movie, pathStack );
	// add no if it reaches here after adding movie
	if( !pathStack.isEmpty() ) {
	  pathStack.push( T->QorA + " no" );
	}
	// if still empty, check yes
	if( pathStack.isEmpty() ) {
	  TracePath( T->yes, movie, pathStack );
		// add yes if it reaches here after adding movie
	    if( !pathStack.isEmpty() )
		  pathStack.push( T->QorA + " yes" );
	}
	// movie is added first
	if( T->QorA == movie ) 
	  pathStack.push( T->QorA );
  }
  return true;
}

void ShowPath(const Stack<string> & pathStack)
{
  Stack<string> path(pathStack);

  while(!path.isEmpty()){
    cout << path.top() << endl;
    path.pop();
  }
}
