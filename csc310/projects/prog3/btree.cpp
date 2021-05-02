#include "btree.h"

BTree::BTree()
{
    rootAddr = -1;
    height = 0;
    read = 0;
    write = 0;
}

////////////////////////////////////////////////////////////////////////////////
// Public
////////////////////////////////////////////////////////////////////////////////

// DONE
// create the header of the file with the correct pointers
// to the root address and initialize the arrays of root
void BTree::writeHeader(char *fileName)
{
    BTNode temp;
    temp.child[0] = sizeof(BTNode);

    treeFile.open(fileName, ios::in | ios::out | ios::binary);
    treeFile.write((char *)&temp, sizeof(BTNode));

    rootAddr = sizeof(BTNode);
    for (int i = 0; i < ORDER; i++)
        root.child[i] = -1;

    root.currSize = 0;
}

// DONE
// [public] inserts keys into the B-Tree
void BTree::insert(keyType key)
{
    cout << "Now Inserting " << key << endl;

    // if the root is empty, we can just shove in the key
    if (root.currSize == 0)
    {
        root.contents[0] = key;
        root.currSize++;
        treeFile.seekp(rootAddr);
        treeFile.write((char *)&root, sizeof(BTNode));
        write++;
    }
    else
        insert(key, findAddr(key, root, rootAddr));
}

// DONE
// clear the treeFile file
void BTree::reset(char *fileName)
{
    if (treeFile)
        treeFile.close();

    treeFile.open(fileName, ios::out | ios::trunc);
    treeFile.close();
}

// DONE
// closes the treeFile file
void BTree::close()
{
    treeFile.close();
}

// DONE
// prints the tree starting from the root address
void BTree::printTree()
{
    printTree(rootAddr);
}

void BTree::inorder()
{
}

void BTree::reverse()
{
}

// DONE
// return the height
int BTree::getHeight()
{
    return height;
}

bool BTree::search(string key)
{
}

keyType BTree::retrieve(string key)
{
}

void BTree::totalio() const
{
}

int BTree::countLeaves()
{
}

////////////////////////////////////////////////////////////////////////////////
// Private
////////////////////////////////////////////////////////////////////////////////

// DONE
// Dr. Digh's printTree
void BTree::printTree(int recAddr)
{
    if (recAddr != -1)
    {
        BTNode temp = getNode(recAddr);
        printNode(recAddr);
        for (int i = 0; i <= temp.currSize; i++)
            printTree(temp.child[i]);
    }
}

void BTree::inorder(int rootAddr)
{
}

void BTree::reverse(int rootAddr)
{
}

// DONE
// find the address of the key
// if it isn't in the tree, get the address of where it would be
int BTree::findAddr(keyType key, BTNode t, int tAddr)
{
    if (isLeaf(t))
        return tAddr;

    int i;
    for (i = 0; i < t.currSize; i++)
        if (key < t.contents[i])
            return findAddr(key, getNode(t.child[i]), t.child[i]);

    // if the loop is at the last child...
    return findAddr(key, getNode(t.child[i]), t.child[i]);
}

// DONE
// find the address of the parent of the node
int BTree::findpAddr(keyType key, BTNode t, int tAddr, int findAddr)
{
    // if we are trying to find the parent of root (non-existent) return -1
    if (findAddr == rootAddr)
        return -1;

    // otherwise check for the key in each of the children
    for (int i = 0; i <= t.currSize; i++)
        if (t.child[i] == findAddr)
            return findAddr;

    // check contents for the key we need
    int i;
    for (i = 0; i < t.currSize; i++)
        if (key < t.contents[i])
            return findpAddr(key, getNode(t.child[i]), t.child[i], findAddr);

    // if the loop is at the last child...
    return findpAddr(key, getNode(t.child[i]), t.child[i], findAddr);
}

void BTree::insert(keyType key, int recAddr)
{
    BTNode currNode = getNode(recAddr);

    // if we don't need splits
    if (currNode.currSize < ORDER - 1)
    {
        // add the key to that node and sort
        currNode.contents[currNode.currSize] = key;
        currNode.currSize++;
        sort(currNode.contents, currNode.contents + currNode.currSize);

        // write it out to the file and increment write operations
        treeFile.seekp(recAddr);
        treeFile.write((char *)&currNode, sizeof(BTNode));
        write++;

        // keep everything in relation to root
        if (recAddr == rootAddr)
            root = currNode;
    }
}

// DONE
// seek in the tree to the node's address then read in the node data and return it
BTNode BTree::getNode(int recAddr)
{
    treeFile.seekg(recAddr);
    BTNode temp;
    treeFile.read((char *)&temp, sizeof(BTNode));
    read++;

    return temp;
}

// DONE
// Dr. Digh's printNode function
void BTree::printNode(int recAddr)
{
    treeFile.seekg(recAddr, ios::beg);
    BTNode temp;
    treeFile.read((char *)&temp, sizeof(BTNode));
    read++;

    cout << "    *** node of size " << temp.currSize << " ***    " << endl;
    for (int i = 0; i < temp.currSize; i++)
        cout << temp.contents[i] << endl;
}

void BTree::placeNode(keyType k, int recAddr, int oneAddr, int twoAddr)
{
}

// DONE
// calls the private isLeaf function with the node associated with the address
bool BTree::isLeaf(int recAddr)
{
    return isLeaf(getNode(recAddr));
}

// DONE
// return if the first child is a null link, therefore no links exist
bool BTree::isLeaf(BTNode t)
{
    return t.child[0] == -1;
}

int BTree::countLeaves(int recAddr)
{
}

void BTree::adjRoot(keyType rootElem, int oneAddr, int twoAddr)
{
}

void BTree::splitNode(keyType &key, int recAddr, int &oneAddr, int &twoAddr)
{
}

bool BTree::search(string key, BTNode t, int tAddr)
{
}
