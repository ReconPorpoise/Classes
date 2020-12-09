#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <sstream>
#include "graph.h"
using namespace std;

void buildGraph(Graph<string>& myGraph, string fileName, vector<string> &vertices);
int findIndex(vector<string> vertices, int numVertices, string toFind);
void createArrs(vector<string> vertices, vector<bool>& marked, vector<int>& distance, vector<string>& prev, int numVertices);
void printRow(string origin, int distance, string previ);
int findMin(vector<bool>& marked, vector<int>& distance);
void sortVertices(vector<string> vertices);
void sortAll(vector<string>& vertices, vector<bool>& marked, vector<int>& dist, vector<string>& prev);
void doDijkstras(Graph<string> graph, vector<string> vertices);

////////////////////////////////////////////////////////////////////////////////
// works!
int main(int argc, char *argv[])
{
    // file I/O: check if the filename is given, if it is, check if it's correct
    string fileName;
    if (argv[1] != NULL)
        fileName = argv[1];
    else
    {
        cout << "Bad input. Try again." << endl;
        return 0;
    }

    ifstream infile;
    infile.open(fileName);
    if (!infile)
    {
        cout << "File name is incorrect.\nTry again." << endl;
        infile.close();
        return 0;
    }
    infile.close();

    // create a vector that holds all vertices
    // and a graph with all vertices
    vector<string> vertices;
    Graph<string> myGraph;
    buildGraph(myGraph, fileName, vertices);
    
    // send off the graph and vertices vector to the main logic function 
    doDijkstras(myGraph, vertices);

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// works!
void buildGraph(Graph<string>& myGraph, string fileName, vector<string> &vertices)
{
    ifstream infile;
    infile.open(fileName);

    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        string curr;
        vector<string> pieces;
        // cuts the input line into 3 parts
        while (getline(ss, curr, ';'))
        {
            pieces.push_back(curr);
        }
        // builds the graph and vertices vector
        if(find(vertices.begin(), vertices.end(), pieces[0]) == vertices.end())
        {
            myGraph.AddVertex(pieces[0]);
            vertices.push_back(pieces[0]);
        }
        if(find(vertices.begin(), vertices.end(), pieces[1]) == vertices.end())
        {
            myGraph.AddVertex(pieces[1]);
            vertices.push_back(pieces[1]);
        }
        myGraph.AddEdge(pieces[0], pieces[1], stoi(pieces[2]));

        pieces.clear();
    }
}
////////////////////////////////////////////////////////////////////////////////
// works!
int findIndex(vector<string> vertices, int numVertices, string toFind) 
{
    int index;

    // search the vector to look for the given vertex value, 
    // then return the index value of that vertex. 
    for(int i = 0; i < numVertices; i++) 
    {
        if(vertices[i].compare(toFind) == 0) 
        {
            index = i;
            return index;
        }
    }
    
    // if it's not found, return a -1
    return -1;
}
////////////////////////////////////////////////////////////////////////////////
// works!
void createArrs(vector<string> vertices, vector<bool>& marked, vector<int>& distance, vector<string>& prev, int numVertices) 
{
    // fill all arrays with generic values EXCEPT for the vertices list
    for(int i = 0; i < numVertices; i++) 
    {
        marked.push_back(false);
        distance.push_back(INT_MAX);
        prev.push_back("---");
    }
}
////////////////////////////////////////////////////////////////////////////////
// works!
void printRow(string origin, int distance, string previ)
{
    if(distance == 2000000000)
        printf("%30s %30s %30s \n", origin.c_str(), "Not on Path", "N/A");
    else
        printf("%30s %30d %30s \n", origin.c_str(), distance, previ.c_str());
    
}
////////////////////////////////////////////////////////////////////////////////
// works!
int findMin(vector<bool>& marked, vector<int>& distance)
{
    int lowIndex;  
    bool found = false;
    int i = 0;
    while(!found && i < distance.size())
    {
        if(marked[i] == false) 
        {
            lowIndex = i;
            found = true;
        } 
        i++;
    }

    i = 1;
    while(i < marked.size())
    {
        if(distance[i] < distance[lowIndex] && marked[i] == false)
            lowIndex = i;
        i++;
    }

    return lowIndex;
}
////////////////////////////////////////////////////////////////////////////////
// works!
void sortVertices(vector<string> vertices)
{
    sort(vertices.begin(), vertices.end());
    int numVertices = vertices.size();

    cout << "--------------- Dijkstra's Algorithm Program ---------------\n\n";
    cout << "A Weighted Graph has been Build for these " << numVertices << " Cities:\n" << endl;
    for(int i = 0; i < numVertices; i++) 
    {
        if(i % 2 == 0 && i != 0)
            printf("%30s \n", vertices[i].c_str());
        else 
            printf("%30s", vertices[i].c_str());
    }  
}
////////////////////////////////////////////////////////////////////////////////
// works!
void sortAll(vector<string>& vertices, vector<bool>& marked, vector<int>& dist, vector<string>& prev)
{
    int dSize = dist.size();
    for(int i = 0; i < dSize; i++)
    {
        for(int j = 0; j < dSize - i - 1; j++)
        {
            if(dist[j] > dist[j+1])
            {
                string verTemp = vertices[j];
                vertices[j] = vertices[j+1];
                vertices[j+1] = verTemp;

                bool marTemp = marked[j];
                marked[j] = marked[j+1];
                marked[j+1] = marTemp;

                int disTemp = dist[j];
                dist[j] = dist[j+1];
                dist[j+1] = disTemp;

                string preTemp = prev[j];
                prev[j] = prev[j+1];
                prev[j+1] = preTemp;
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
// works!
void doDijkstras(Graph<string> graph, vector<string> vertices) 
{
    // diplay all cities to the user
    sortVertices(vertices);

    // initialize blank vectors
    vector<bool> marked;
    vector<int> distance;
    vector<string> prev;
    
    // create the queue and the number of vertices
    Queue<string> graphQueue;
    int numVertices = vertices.size();

    // ask user for starting vertex and check if it's valid.
    // if it's not, keep asking.
    string startingPoint = "";
    bool found = false;
    while(!found) 
    {
        cout << "\nEnter a starting vertex: ";
        getline(cin, startingPoint);
        for(int i = 0; i < numVertices; i++) 
        {
            if(findIndex(vertices, numVertices, startingPoint) != -1) 
            {
                found = true;
                break;
            }
            else 
            {
                cout << "Not a vertex... Try again." << endl;
                break;
            }
        }
    }
    int startIndex = findIndex(vertices, numVertices, startingPoint);
    graph.MarkVertex(startingPoint);

    // create the adjacent arrays with default values
    createArrs(vertices, marked, distance, prev, numVertices);

    // update adjacent arrays for the starting vertex
    marked[startIndex] = true;
    distance[startIndex] = 0;
    prev[startIndex] = "N/A";

    // find vertices adjacent to starting vertex and add them to a temp vector
    for(int i = 0; i < numVertices - 1; i++) 
    {
        graph.GetToVertices(startingPoint, graphQueue);
        vector<string> adjacents;
        while(!graphQueue.isEmpty())
        {
            adjacents.push_back(graphQueue.dequeue());
        }

        // check each adjacent point
        for(int i = 0; i < adjacents.size(); i++) 
        {
            // if it's not marked...
            if(!graph.IsMarked(adjacents[i])) 
            {
                // get its weight, then compare it
                int currIndex = findIndex(vertices, numVertices, adjacents[i]);
                int weight = graph.WeightIs(startingPoint, adjacents[i]) + distance[startIndex];
                if( weight < distance[currIndex]) 
                {
                    prev[currIndex] = startingPoint;
                    distance[currIndex] = weight;
                }
            }
        }  
        adjacents.empty();
        startIndex = findMin(marked, distance);
        marked[startIndex] = true;
        startingPoint = vertices[startIndex];
    }
    cout << "--------------------------------------------------------------------------------------------\n";
    printf("%30s %30s %30s \n", "Vertex", "Distance", "Previous");
    printf("%30s %30s %30s", "------", "--------", "--------");

    cout << endl;
    for(int i = 0; i < numVertices; i++)
        if(distance[i] > 2000000000 || distance[i] < 0) 
            distance[i] = 2000000000;

    sortAll(vertices, marked, distance, prev);
    for(int i = 0; i < numVertices; i++)
        printRow(vertices[i], distance[i], prev[i]);
}
