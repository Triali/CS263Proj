//
// Created by elton on 4/4/2023.
//

#ifndef CS236PROJ_GRAPH_H
#define CS236PROJ_GRAPH_H

#include <map>
#include "Node.h"

using namespace std;
class Graph
{
private:

    map<int,Node> nodes;

public:

    Graph(int size);
    // passed the number of nodes to create in the graph.
    // Nodes are then created with node IDs from 0 to size-1

    void addEdge(int fromNodeID, int toNodeID);
    // adds adge from fromNode to toNode

    string toString();
    // return ID : adjacent nodes
    // ie R1:R2,R3,R4

};



#endif //CS236PROJ_GRAPH_H
