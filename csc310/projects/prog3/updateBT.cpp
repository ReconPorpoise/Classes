#include <fstream>
#include <iostream>
#include "album.h"
#include "btree.h"
using namespace std;

int main(int argc, char **argv)
{
    char *inTree = argv[1];
    char *trans = argv[2];

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
            cout << toFind << endl;
            bool ifFound = tree.search(toFind);
            if (ifFound)
                cout << toFind << " was found." << endl;
            else
                cout << toFind << " was not found." << endl;
        }
        if (instr == 'I')
        {
            transactions >> tempRecord;
            tree.insert(tempRecord);
            cout << tempRecord << " was inserted." << endl;
        }
    }

    tree.totalio();
    transactions.close();
    tree.close();
}