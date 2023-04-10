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
        out << "R" << nodeID << ": ";

        // add adjacent nodes to string
        out << node.adjNodetoString() << endl;
    }




    return out.str();
}
int Graph::size()
{
    return nodes.size();
}

set<int> Graph::getAvailableNodes(int nodeID)
{
    set<int> availNodes;
    // create an empty set of node ids
    Node* node = &nodes.find(nodeID)->second;
    // find the specific node referenced in fuction call
    set<int> adjNodes = node->getAdjacentNodeIDs();
    // get set of adj node from called node

    // for each id in that set
    for(auto& ID : adjNodes)
    {
        Node* adjNode = &nodes.find(ID)->second;

        //check if it has been visited
        if(!adjNode->isVisited())
        {
            // if it has not been visited, add to empty set
            availNodes.insert(ID);
        }
    }

    return availNodes;
}
