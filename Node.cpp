//
// Created by elton on 4/4/2023.
//

#include "Node.h"

Node::Node()
{
    nodeID = -1;
    visited = false;
}


void Node::addEdge(int adjacentNodeID)
{
    adjacentNodeIDs.insert(adjacentNodeID);
}

string Node::adjNodetoString()
{
    stringstream out;
    int count = 0;
    // gives a number to compare to the size of the set
    for (auto& id : adjacentNodeIDs)
    {

        out << "R" << id;

        // while count is not at the end of the set, add a comma
        if(count != static_cast<int>(adjacentNodeIDs.size() -1))
        // is count at the last postion in the set?
        {
            out << " ";
        }
        count++;
        //increase count

    }

        return out.str();
}

