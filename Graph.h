//
// Created by elton on 4/4/2023.
//

#ifndef CS236PROJ_GRAPH_H
#define CS236PROJ_GRAPH_H

#include <map>
#include <vector>
#include "Node.h"
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;
class Graph
{
private:

    map<int, Node> nodes;
    vector<int> order;


public:

    Graph(int size);
    // passed the number of nodes to create in the graph.
    // Nodes are then created with node IDs from 0 to size-1

    Node *getNode(int ID);

    void addEdge(int fromNodeID, int toNodeID);
    // adds adge from fromNode to toNode

    string toString();
    // return ID : adjacent nodes
    // ie R1:R2,R3,R4

    int size();
    // returns size of map

    void addChildren(int nodeID);
    //recursively works through the nodes in numerical order

    vector<int> getOrder();

    string orderToString();

    void setOrder(vector<int> order);

    void addPostOrder(int nodeID, set<int>& scc);
// recurseivly works through the nodes in the precednace order given by order vector;


};

#endif //CS236PROJ_GRAPH_H
