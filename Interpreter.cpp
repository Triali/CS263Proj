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
                if(rulename == predName)
                {
//                    cout << "dependency found: (R" << fromID << ",R" << toID << ")" << endl;
                    graph.addEdge(fromID,toID);
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
                if(rulename == predName)
                {
//                    cout << "dependency found: (R" << f
//                    .romID << ",R" << toID << ")" << endl;
                    graph.addEdge(toID,fromID);
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


    Graph graph = makeGraph();
    out << graph.toString() << endl;
    Graph revGraph = makeReverseGraph();
    out << revGraph.toString() << endl;

    



    return out.str();

}

