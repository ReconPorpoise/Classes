#include <fstream>
#include <iostream>
#include "album.h"
#include "btree.h"
using namespace std;

int main(int argc, char **argv)
{
    char *in = argv[1];
    char *out = argv[2];

    fstream infile;
    infile.open(in, ios::in);

    BTree tree;
    tree.reset(out);
    tree.writeHeader(out);

    Album temp;
    while (infile >> temp)
        tree.insert(temp);

    tree.printTree();

    // cout << boolalpha << tree.search("42276") << endl;
    // cout << boolalpha << tree.search("1234123") << endl;

    infile.close();
    tree.close();
}