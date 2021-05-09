#include <fstream>
#include <iostream>
#include "album.h"
#include "btree.h"
using namespace std;

bool argCheck(char *inFile, char *treeFile);
void printError();

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printError();
        return 1;
    }

    char *in = argv[1];
    char *out = argv[2];

    if (!argCheck(in, out))
    {
        return 1;
    }

    fstream infile;
    infile.open(in, ios::in);

    BTree tree;
    tree.reset(out);
    tree.writeHeader(out);

    Album temp;
    while (infile >> temp)
        tree.insert(temp);

    tree.printTree();

    infile.close();
    tree.close();
}

bool argCheck(char *inFile, char *treeFile)
{
    fstream testIn(inFile);
    fstream testTree(treeFile);

    // check if the tree file is valid
    if (!(testIn.is_open()))
    {
        testIn.close();
        testTree.close();

        cout << "myCreate: Incorrect album file: " << inFile << " does not exist." << endl;
        printError();
        return false;
    }
    testIn.close();

    // check if the transaction file is valid
    if (!(testTree.is_open()))
    {
        testIn.close();
        testTree.close();

        cout << "myCreate: Incorrect tree file: " << treeFile << " does not exist." << endl;
        printError();
        return false;
    }
    testTree.close();

    return true;
}

void printError()
{
    cout << "myCreate: Must have 2 files in the format of ./myCreate <album.ext file> <tree.ind file>." << endl;
}