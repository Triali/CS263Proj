#include <iostream>
#include <fstream>
#include "Token.h"
#include "Scanner.h"
#include <string>
#include "Parser.h"
#include "Node.h"
#include "Graph.h"
#include "Interpreter.h"


int main(int argc, char *argv[])
{
    string fileName = argv[1];
    stringstream write;
//    cout << "file name: " << fileName << endl;

    ifstream myfile;
    string input;
    myfile.open(fileName);
    while (!myfile.eof())
    {
        string sub;
        getline(myfile, sub);//make a loop for reading whole file
        input = input + sub + "\n";
    }
    input.pop_back();
    myfile.close();
//cout << "Scanner" << endl;
    Scanner t = Scanner(input);
    t.scanAll();


//    t.PrintOutput();
//    cout << endl << endl;
    string outputScanner = t.TokenVectorToString();
    vector<Token> tokens = t.getTokenList();
    Parser p = Parser(tokens);

//    cout << "Parser" << endl;
    string outputParser = p.parse();
//   cout << outputParser << endl << endl;
    Interpreter inter(p);
    write << inter.interpreteGraph();


    cout << write.str()<< endl;
//    ofstream outputFile;
//    outputFile.open("output.txt");
//    outputFile << write.str();
//    outputFile.close();

}


//int main() {
//
//    // predicate names for fake rules
//    // first is name for head predicate
//    // second is names for body predicates
//    pair<string,vector<string>> ruleNames[] = {
//            { "A", { "B", "C" } },
//            { "B", { "A", "D" } },
//            { "B", { "B" } },
//            { "E", { "F", "G" } },
//            { "E", { "E", "F" } },
//    };
//
//    vector<Rule> rules;
//
//    for (auto& rulePair : ruleNames) {
//        string headName = rulePair.first;
//        Rule rule = Rule(Predicate(headName));
//        vector<string> bodyNames = rulePair.second;
//        for (auto& bodyName : bodyNames)
//            rule.addPredicate(Predicate(bodyName));
//        rules.push_back(rule);
//    }
//
//    Graph graph = Interpreter::makeGraph(rules);
//    cout << graph.toString();
//
//}