#include <fstream>
#include <iostream>
#include "album.h"
#include "btree.h"
using namespace std;

bool argCheck(char *infile, char *transFile);
void printError();

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printError();
        return 1;
    }

    char *inTree = argv[1];
    char *trans = argv[2];

    if (!argCheck(inTree, trans))
    {
        return 1;
    }

    BTree tree;
    Album tempRecord;

    fstream transactions;
    transactions.open(trans, ios::in);
    tree.defineRoot(inTree);

    char instr;
    while (transactions >> instr)
    {
        transactions.ignore(1, '\n');
        if (instr == 'S')
        {
            string toFind;
            getline(transactions, toFind);
            bool ifFound = tree.search(toFind);
            if (ifFound)
            {
                Album toPrint = tree.retrieve(toFind);
                cout << "\t" << toPrint << endl;
            }
            else
                cout << "\t"
                     << "\"" << toFind << "\" not found" << endl;
        }
        if (instr == 'I')
        {
            transactions >> tempRecord;
            tree.insert(tempRecord);
        }
    }

    cout << endl;
    tree.totalio();
    transactions.close();
    tree.close();
}

bool argCheck(char *infile, char *transFile)
{
    fstream testIn(infile);
    fstream testTrans(transFile);

    // check if the tree file is valid
    if (!(testIn.is_open()))
    {
        testIn.close();
        testTrans.close();

        cout << "myUpdate: Incorrect tree file: " << infile << " does not exist." << endl;
        printError();
        return false;
    }
    testIn.close();

    // check if the transaction file is valid
    if (!(testTrans.is_open()))
    {
        testIn.close();
        testTrans.close();

        cout << "myUpdate: Incorrect transaction file: " << transFile << " does not exist." << endl;
        printError();
        return false;
    }
    testTrans.close();

    return true;
}

void printError()
{
    cout << "myUpdate: Must have 2 files in the format of ./myUpdate <tree.ind file> <transaction.dat file>." << endl;
}
