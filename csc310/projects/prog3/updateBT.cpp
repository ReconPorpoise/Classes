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
