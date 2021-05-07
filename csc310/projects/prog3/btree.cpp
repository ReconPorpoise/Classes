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
    write++;
}

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

// clear the treeFile file
void BTree::reset(char *fileName)
{
    if (treeFile)
        treeFile.close();

    treeFile.open(fileName, ios::out | ios::trunc);
    treeFile.close();
}

// closes the treeFile file
void BTree::close()
{
    treeFile.close();
}

// prints the tree starting from the root address
void BTree::printTree()
{
    cout << "---- B-Tree of Height " << getHeight() << " ----" << endl;
    printTree(rootAddr);
}

void BTree::inorder()
{
    inorder(rootAddr);
}

void BTree::reverse()
{
    reverse(rootAddr);
}

// return the height
int BTree::getHeight()
{
    return height;
}

bool BTree::search(string key)
{
    return search(key, root, rootAddr);
}

keyType BTree::retrieve(string key)
{
    return retrieve(key, root, rootAddr);
}

void BTree::totalio() const
{
    cout << "Read: " << read << endl;
    cout << "Write: " << write << endl;
}

int BTree::countLeaves()
{
    return countLeaves(rootAddr);
}

void BTree::defineRoot(char *fileName)
{
    treeFile.open(fileName, ios::in | ios::out | ios::binary);
    BTNode temp;
    treeFile.seekg(0, ios::beg);
    treeFile.read((char *)&temp, sizeof(BTNode));
    rootAddr = temp.child[0];
    root = getNode(temp.child[0]);
    read++;
}

////////////////////////////////////////////////////////////////////////////////
// Private
////////////////////////////////////////////////////////////////////////////////

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

// inorder traversal
void BTree::inorder(int rootAddr)
{
    if (rootAddr == -1)
        return;
    BTNode tempNode = getNode(rootAddr);
    int i;
    for (i = 0; i < tempNode.currSize; i++)
    {
        inorder(tempNode.child[i]);
        cout << tempNode.contents[i] << endl;
    }
    inorder(tempNode.child[i]);
}

// reverse inorder traversal
void BTree::reverse(int rootAddr)
{
    if (rootAddr == -1)
        return;
    BTNode tempNode = getNode(rootAddr);
    int i;
    for (i = tempNode.currSize; i >= 0; i--)
    {
        if (i < tempNode.currSize)
            cout << tempNode.contents[i] << endl;
        reverse(tempNode.child[i]);
    }
}

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

// find the address of the parent of the key we need to insert
int BTree::findpAddr(keyType key, BTNode t, int tAddr, int findAddr)
{
    // if we are trying to find the parent of root (non-existent) return -1
    if (findAddr == rootAddr)
        return -1;

    // otherwise check for the key in each of the children
    for (int i = 0; i <= t.currSize; i++)
        if (t.child[i] == findAddr)
            return tAddr;

    // check contents for the key we need
    int i;
    for (i = 0; i < t.currSize; i++)
        if (key < t.contents[i])
            return findpAddr(key, getNode(t.child[i]), t.child[i], findAddr);

    // if the loop is at the last child...
    return findpAddr(key, getNode(t.child[i]), t.child[i], findAddr);
}

// insert nodes into the b-tree
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
    // splitting
    else
    {
        int ghostAddr;
        splitNode(key, recAddr, ghostAddr);
    }
}

// seek in the tree to the node's address then read in the node data and return it
BTNode BTree::getNode(int recAddr)
{
    treeFile.seekg(recAddr);
    BTNode temp;
    treeFile.read((char *)&temp, sizeof(BTNode));
    read++;

    return temp;
}

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

// actually promotes the median from a split
void BTree::placeNode(keyType key, int pAddr, int leftAddr, int rightAddr)
{
    BTNode parentNode = getNode(pAddr);

    // check if node we are pushing to is not full
    if (parentNode.currSize < ORDER - 1)
    {
        // sort the contents array but make sure to keep the children alligned as well if needed
        if (parentNode.contents[parentNode.currSize - 1] > key)
        {
            int shift = 0;
            while (key > parentNode.contents[shift] && shift < parentNode.currSize)
                shift++;

            int end = parentNode.currSize - 1;
            while (end >= shift)
            {
                parentNode.contents[end + 1] = parentNode.contents[end];
                parentNode.child[end + 2] = parentNode.child[end + 1];
                end--;
            }

            parentNode.contents[shift] = key;
            parentNode.child[shift + 1] = rightAddr;
            parentNode.currSize++;
        }
        // if we don't need to rearrange, set the content/child accordingly at the end
        else
        {
            parentNode.contents[parentNode.currSize++] = key;
            parentNode.child[parentNode.currSize] = rightAddr;
        }

        // write the changes to the file
        treeFile.seekp(pAddr);
        treeFile.write((char *)&parentNode, sizeof(BTNode));
        write++;

        if (pAddr == rootAddr)
            root = parentNode;
    }
    else
        splitNode(key, pAddr, rightAddr);
}

// calls the private isLeaf function with the node associated with the address
bool BTree::isLeaf(int recAddr)
{
    return isLeaf(getNode(recAddr));
}

// return if the first child is a null link, therefore no links exist
bool BTree::isLeaf(BTNode t)
{
    return t.child[0] == -1;
}

// return the number of leaves in the B-Tree
int BTree::countLeaves(int recAddr)
{
    BTNode tempNode = getNode(recAddr);
    if (isLeaf(tempNode))
        return 1;
    else
    {
        int leaves = 0;
        for (int i = 0; i <= tempNode.currSize; i++)
            leaves += countLeaves(tempNode.child[i]);
        return leaves;
    }
}

// rewrites the root when a split occurs
void BTree::adjRoot(keyType rootElem, int oneAddr, int twoAddr)
{
    cout << "Now Adjusting Root!" << endl;
    height++;

    // set the correct left/right children for the new root node then write it out to treeFile
    BTNode newRoot;
    newRoot.currSize = 1;
    newRoot.contents[0] = rootElem;
    newRoot.child[0] = oneAddr;
    newRoot.child[1] = twoAddr;
    for (int i = 2; i < ORDER; i++)
        newRoot.child[i] = -1;

    treeFile.seekp(0, ios::end);
    rootAddr = treeFile.tellp();
    root = newRoot;
    treeFile.write((char *)&newRoot, sizeof(BTNode));
    write++;

    BTNode temp;
    temp.child[0] = rootAddr;
    treeFile.seekp(0, ios::beg);
    treeFile.write((char *)&temp, sizeof(BTNode));
    write++;
}

// splits the nodes when a node is filled
void BTree::splitNode(keyType &key, int recAddr, int rAddr)
{
    cout << "Now Splitting!" << endl;
    BTNode currNode = getNode(recAddr);

    // if the split is occurring at a leaf...
    if (isLeaf(currNode))
    {
        BTNode right;

        if (currNode.contents[currNode.currSize - 1] > key)
        {
            keyType temp;
            temp = currNode.contents[currNode.currSize - 1];
            currNode.contents[currNode.currSize - 1] = key;
            key = temp;

            sort(currNode.contents, currNode.contents + currNode.currSize);
        }

        // hides the extra right-node stuff
        // currNode becomes the left node
        currNode.currSize = 2;

        // only fill this node with the 2 nodes to the right of the split median
        right.currSize = 2;
        right.contents[0] = currNode.contents[3];
        right.contents[1] = key;

        // set the links in the new nodes to -1 (null)
        for (int i = 0; i < ORDER; i++)
            right.child[i] = -1;

        // write the left and right nodes to the file (left is just overwrite of curr)
        treeFile.seekp(recAddr);
        treeFile.write((char *)&currNode, sizeof(BTNode));
        treeFile.seekp(0, ios::end);
        rAddr = treeFile.tellp();
        treeFile.write((char *)&right, sizeof(BTNode));
        write += 2;

        // this checks if the root was split, if it was, run adjRoot to set the new root
        // otherwise, push up the median to the parent node
        int parentAddr = findpAddr(key, root, rootAddr, recAddr);
        if (parentAddr == -1)
            adjRoot(currNode.contents[2], recAddr, rAddr);
        else
            placeNode(currNode.contents[2], parentAddr, recAddr, rAddr);
    }
    else
    {
        // chain split
        if (currNode.contents[currNode.currSize - 1] > key)
        {
            keyType keyTemp = currNode.contents[currNode.currSize - 1];
            int rAddrTemp = currNode.child[currNode.currSize];
            currNode.currSize--;

            int shift = 0;
            while (key > currNode.contents[shift] && shift < currNode.currSize)
                shift++;

            int end = currNode.currSize - 1;
            while (end >= shift)
            {
                currNode.contents[end + 1] = currNode.contents[end];
                currNode.child[end + 2] = currNode.child[end + 1];
                end--;
            }

            currNode.contents[shift] = key;
            currNode.child[shift + 1] = rAddr;

            key = keyTemp;
            rAddr = rAddrTemp;
        }

        int parentAddr = findpAddr(key, root, rootAddr, recAddr);
        currNode.currSize = 2;

        // create the right node as we did above, creating the contents and children for it
        BTNode right;
        right.currSize = 2;
        right.contents[0] = currNode.contents[3];
        right.contents[1] = key;

        right.child[0] = currNode.child[3];
        right.child[1] = currNode.child[4];
        right.child[2] = rAddr;

        // initialize all children of the node to -1 (null)
        for (int i = 3; i < ORDER; i++)
            right.child[i] = -1;

        // write out the adjustments to the treeFile
        treeFile.seekp(recAddr);
        treeFile.write((char *)&currNode, sizeof(BTNode));
        treeFile.seekp(0, ios::end);
        rAddr = treeFile.tellp();
        treeFile.write((char *)&right, sizeof(BTNode));
        write += 2;

        // check if the root was split, if it was, run adjRoot to set the new root
        // otherwise, push up the median to the parent node
        if (parentAddr == -1)
            adjRoot(currNode.contents[2], recAddr, rAddr);
        else
            placeNode(currNode.contents[2], parentAddr, recAddr, rAddr);
    }
}

// use the same logic as findAddr but break when we find the key
bool BTree::search(string key, BTNode t, int tAddr)
{
    int i = 0;
    while (i < t.currSize && strcmp(key.c_str(), t.contents[i].getUPC().c_str()) > 0)
        i++;
    if (strcmp(t.contents[i].getUPC().c_str(), key.c_str()) == 0)
        return true;
    if (isLeaf(t))
        return false;
    return search(key, getNode(t.child[i]), t.child[i]);
}

// same as search, but return the album not a bool
keyType BTree::retrieve(string key, BTNode t, int tAddr)
{
    keyType vnf;
    int i;
    for (i = 0; i < t.currSize; i++)
    {
        if (key == t.contents[i].getUPC())
            return t.contents[i];
        if (key < t.contents[i].getUPC())
            return retrieve(key, getNode(t.child[i]), t.child[i]);
    }
    // if the loop is at the last child...
    if (isLeaf(t))
        return vnf;
    return retrieve(key, getNode(t.child[i]), t.child[i]);
}
