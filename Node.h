//
// Created by elton on 4/4/2023.
//

#ifndef CS236PROJ_NODE_H
#define CS236PROJ_NODE_H
#include <set>
#include <string>
#include <sstream>

using namespace std;
class Node {
    // represents a rule in the graph(each rule becomes a node)


private:

    int nodeID;
    // the ID of the node

    set<int> adjacentNodeIDs;
    // stores a set of adjacency nodes(nodes you can travel to in one step)
    // each node in this set represents an

    bool visited;
    //has this nod been visited

    // int postOrderNumber;
    // number in post order traversal of the graph


public:

    Node();
    // sets id to -1, visited to false

    void addEdge(int adjacentNodeID);
    // adds an edge(node ID) to adjacent nodes vector

    string adjNodetoString();
    // returns a string of the ids of the adjacent nodes
    //ei R1,R2,R4 etc

};

#endif //CS236PROJ_NODE_H
