//
// Created by elton on 4/4/2023.
//

#include "Graph.h"

Graph::Graph(int size)
{
    for (int nodeID = 0; nodeID < size; nodeID++)
        nodes[nodeID] = Node();
}

void Graph::addEdge(int fromNodeID, int toNodeID)
{
    nodes[fromNodeID].addEdge(toNodeID);
}

string Graph::toString()
{
    stringstream out;

    for (auto &pair: nodes)
    {
        int nodeID = pair.first;
        // gives you the key to map
        Node node = pair.second;
        // gives tou the node associated with the key

        // add ID to string
        out << "R" << nodeID << ":";

        // add adjacent nodes to string
        out << node.adjNodetoString() << endl;
    }


    return out.str();
}
