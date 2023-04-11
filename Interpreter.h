//
// Created by elton on 4/4/2023.
//

#ifndef CS236PROJ_INTERPRETER_H
#define CS236PROJ_INTERPRETER_H


#include "Parser.h"
#include "Graph.h"
#include "Database.h"

class Interpreter
{
private:
    vector<Predicate> schemes;
    vector<Predicate> queries;
    vector<Rule> rules;
    vector<Predicate> facts;
public:
    Interpreter(Parser p);

    string interprete();
    // runs the interpreter
    //create a database, ises process of lab 4
    //process rules and queries

    Graph makeGraph();
    //returns a Graph that represents the dependencies between the rules

    Graph makeReverseGraph();
    // creates the reverse dependencies graph


    string interpreteGraph();
    // interprete rules using a graph

    vector<int> DFSF(Graph graph);

    vector<set<int>>RDFSF(Graph graph);

};


#endif //CS236PROJ_INTERPRETER_H
