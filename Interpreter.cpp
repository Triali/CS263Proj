//
// Created by elton on 4/4/2023.
//

#include "Interpreter.h"

Interpreter::Interpreter(Parser p)
{
    schemes = p.getDatalogProgram().getSchemeVect();
    queries = p.getDatalogProgram().getQueryVect();
    rules = p.getDatalogProgram().getRuleVect();
    facts = p.getDatalogProgram().getFactVect();

}

string Interpreter::interprete()
{
    stringstream out;

    Database dB = Database(schemes, facts);
    out << dB.EvaluateRules(rules);
    out << dB.ProcessQueries(queries);

    return out.str();
}

Graph Interpreter::makeGraph()
{
    // creates a graph the same size as the rules(just as many nodes
    Graph graph(rules.size());
    //loops over the rules
    for (int fromID = 0; fromID < static_cast<int>(rules.size()); fromID++)
    {
        //gets rule
        Rule fromRule = rules.at(fromID);
        // prints out each rule
//        cout << "from rule R" << fromID << ": " << fromRule.RuleToString() << endl;

//        loop over the predicates of each rule
        for (int pred = 1; pred < static_cast<int>(fromRule.size()); pred++)
        {
            // get predicate
            Predicate bodyPred = fromRule.at(pred);
            //print predicate
//            cout << "from body predicate: " << bodyPred.PredicateToString() << endl;
            // the predicate name
            string predName = bodyPred.getName();

            // loop over the rules
            for (unsigned toID = 0; toID < rules.size(); toID++)
            {
                Rule toRule = rules.at(toID);
//                cout << "to rule R" << toID << ": " << toRule.RuleToString() << endl;
                // this is where I will add edges

                // get the rule name
                string rulename = toRule.at(0).getName();
//                cout << predName << ":: " << rulename << endl;
                if (rulename == predName)
                {
//                    cout << "dependency found: (R" << fromID << ",R" << toID << ")" << endl;
                    graph.addEdge(fromID, toID);
                }
            }
        }

    }
    // add code to add edges to the graph for the rule dependencies
    return graph;


}

Graph Interpreter::makeReverseGraph()
{
    // creates a graph the same size as the rules(just as many nodes
    Graph graph(rules.size());
    //loops over the rules
    for (int fromID = 0; fromID < static_cast<int>(rules.size()); fromID++)
    {
        //gets rule
        Rule fromRule = rules.at(fromID);
        // prints out each rule
//        cout << "from rule R" << fromID << ": " << fromRule.RuleToString() << endl;

//        loop over the predicates of each rule
        for (int pred = 1; pred < static_cast<int>(fromRule.size()); pred++)
        {
            // get predicate
            Predicate bodyPred = fromRule.at(pred);
            //print predicate
//            cout << "from body predicate: " << bodyPred.PredicateToString() << endl;
            // the predicate name
            string predName = bodyPred.getName();

            // loop over the rules
            for (unsigned toID = 0; toID < rules.size(); toID++)
            {
                Rule toRule = rules.at(toID);
//                cout << "to rule R" << toID << ": " << toRule.RuleToString() << endl;
                // this is where I will add edges

                // get the rule name
                string rulename = toRule.at(0).getName();
//                cout << predName << ":: " << rulename << endl;
                if (rulename == predName)
                {
//                    cout << "dependency found: (R" << f
//                    .romID << ",R" << toID << ")" << endl;
                    graph.addEdge(toID, fromID);
                }
            }
        }

    }
    // add code to add edges to the graph for the rule dependencies
    return graph;


}

string Interpreter::interpreteGraph()
{
    stringstream out;

    Database dB = Database(schemes, facts);
    Graph graph = makeGraph();
    out << "Dependency Graph" << endl << graph.toString() << endl;
    Graph revGraph = makeReverseGraph();
//    out << revGraph.toString() << endl;

//    cout << "running recursion" << endl;
    vector<int> order = DFSF(revGraph);
    reverse(order.begin(), order.end());

//    for (int i = 0; i < order.size(); ++i)
//    {
//        out << order.at(i) << " ";
//    }
//    cout << endl;
    graph.setOrder(order);
    vector <set<int>> SCC = RDFSF(graph);
//    out << endl;
//    out << endl;
//    out << "SCC" << endl;
//    for (int i = 0; i < SCC.size(); ++i)
//    {
//        for (auto &j: SCC.at(i))
//        {
//            out << j << " ";
//        }
//        out << endl;
//    }
    out << "Rule Evaluation" << endl;
    for (int i = 0; i < SCC.size(); ++i)
    {
        out << "SCC: ";
//        out << "(Size "<<SCC.at(i).size()<< ")"<< endl;
        int count = 0;
        for (auto &j: SCC.at(i))
        {
            out << "R" << j;
            // while count is not at the end of the set, add a comma
            if (count != static_cast<int>(SCC.at(i).size() - 1))
                // is count at the last postion in the set?
            {
                out << ",";
            }
            count++;
            //increase count
        }
//        out << endl;
        vector <Rule> ruleSet;
        for (auto &j: SCC.at(i))
        {
            ruleSet.push_back(rules.at(j));
        }
        bool solo = false;
        out << endl;


        if (SCC.at(i).size() == 1)
        {

//            cout <<endl<< "size 1" << endl;
            auto it = SCC.at(i).begin();
//            cout <<i << "::"<< *it<< endl;
            int id = *it;
//            cout << graph.getNode(*it)->adjNodetoString()<< endl;
            set<int> adj = graph.getNode(id)->getAdjacentNodeIDs();
            if (adj.empty() || adj.find(id) == adj.end())
            {
//                cout << "not self dependant"<< endl;
                solo = true;
            }

        }


//        cout << i << " solo " << solo << endl;
        out << dB.EvaluateRulesG(ruleSet, solo);
        out << ": ";
        count = 0;
        for (auto &j: SCC.at(i))
        {
            out << "R" << j;

            // while count is not at the end of the set, add a comma
            if (count != static_cast<int>(SCC.at(i).size() - 1))
                // is count at the last postion in the set?
            {
                out << ",";
            }
            count++;
            //increase count
        }


        out << endl;

    }
    out << endl << dB.ProcessQueries(queries);





//    out << endl;

    return out.str();

}

vector<int> Interpreter::DFSF(Graph graph)
{

    // recursively call children of eah node to print their children
    // move to next lowest when done
//    cout << "running recursion" << endl;
    for (int i = 0; i < graph.size(); i++)
    {
        graph.addChildren(i);
    }
//    cout <<" recursion done. Size: " << nodeOrder.size()<< endl;


    return graph.getOrder();
}

vector <set<int>> Interpreter::RDFSF(Graph graph)
{
    vector<int> revOrder = graph.getOrder();
    vector <set<int>> SCC;
//    cout << revOrder.size() << endl;
    for (int i = 0; i < revOrder.size(); i++)
    {
//        cout << revOrder.at(i) << ": ";
        set<int> scc;
        graph.addPostOrder(revOrder.at(i), scc);
        if (!scc.empty())
        {
            SCC.push_back(scc);
        }
//        cout << endl;
    }
//    cout << graph.getOrder().size() << endl;
//    cout << endl << endl;
    return SCC;


}



