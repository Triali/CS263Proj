//
// Created by elton on 4/4/2023.
//

#include "Graph.h"


Graph::Graph(int size)
{
    for (int nodeID = 0; nodeID < size; nodeID++)
        nodes[nodeID] = Node();
}

Node *Graph::getNode(int ID)
{
    return &nodes.find(ID)->second;
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

int Graph::size()
{
    return nodes.size();
}

void Graph::addChildren(int nodeID)
{
    Node *node = &nodes.find(nodeID)->second;

    if (!node->isVisited())
    {
        node->Visited();
        for (auto &id: node->getAdjacentNodeIDs())
        {
            addChildren(id);
        }
        order.push_back(nodeID);
//        cout << nodeID << " ";
    }
}

vector<int> Graph::getOrder()
{
    return order;
}

string Graph::orderToString()
{
    stringstream out;
    for (int i = 0; i < static_cast<int>(order.size()); ++i)
    {
        out << order.at(i) << " ";
    }
    return out.str();
}

void Graph::setOrder(vector<int> order)
{
    this->order = order;
}

void Graph::addPostOrder(int nodeID, set<int> &scc)
{
    Node *node = &nodes.find(nodeID)->second;
    set<int> adjNodes = node->getAdjacentNodeIDs();
    // if the node has not been visited
    if (!node->isVisited())
    {
        //mark it as visited
        node->Visited();

//        for each number in order vector
        for (int i = 0; i<static_cast<int>(order.size());i++)
        {

            int id = order.at(i);
            //chech if it is in the adjecent nodes

            if(adjNodes.find(id) != adjNodes.end())
            {
                // if it is, run addPostOrder on that node

                addPostOrder(id, scc);
            }

        }
        //then insert the node into the set
        scc.insert(nodeID);
//        cout  << nodeID << "; ";
    }

}
