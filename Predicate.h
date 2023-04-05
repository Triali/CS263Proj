//
// Created by elton on 2/10/2023.
//

#ifndef CS236PROJ1_PREDICATE_H
#define CS236PROJ1_PREDICATE_H


#include "Parameter.h"
#include <string>
#include <vector>
#include <sstream>
#include "Relation.h"

using namespace std;

class Predicate
{
private:

    string name;
    vector<Parameter> parameters;
    string end;

public:
    //contructor
    Predicate(string name)
    {
        this->name = name;
        end ="";
    }

    //get fuctions

    //get name
    string getName()
    {
        return name;
    }

    void getEnd(string endChar)
    {
        end = endChar;
//        cout << end << endl;
    }
    //get parameters
    vector<Parameter> getParameters()
    {
        return parameters;
    }

    //add parameter
    void AddParameter(Parameter newParameter)
    {
        parameters.push_back(newParameter);
    }

    string PredicateToString()
    {
        stringstream predicateString;
        //add name ( parameter, ... parameter)
        predicateString << "  " <<name << "(";
        for (int i = 0; i < getParaSize(); ++i)
        {
//            add the parameter
            predicateString << parameters.at(i).getValue();
//            add comma if not at the last index of vector
            if (i != getParaSize()-1)
            {
                predicateString << ",";
            }
        }
//        add last paranthisis
        predicateString << ")" << end;
        return predicateString.str();
    }

    vector<string> getParameterNames()
    {
        vector<string> names;
//        cout << "getting parameters into strings" << endl;
        for(int i  = 0; i < static_cast<int>(parameters.size());i++)
        {
//            cout << parameters.at(i).getValue() <<endl;
            names.push_back(parameters.at(i).getValue());
        }
//        cout << " DOne getting parameters into strings" << endl;
        return names;
    }

    Relation PredtoRel()
    {
        Scheme scheme = getParameterNames();

        Relation rel = Relation(name,scheme);
//        cout << rel.toFullString() << endl;
        return rel;
    }

    string PredicateToStringR()
    {
        stringstream predicateString;
        //add name ( parameter, ... parameter)
        predicateString <<name << "(";
        for (int i = 0; i < getParaSize(); ++i)
        {
//            add the parameter
            predicateString << parameters.at(i).getValue();
//            add comma if not at the last index of vector
            if (i != getParaSize()-1)
            {
                predicateString << ",";
            }
        }
//        add last parenthesis
        predicateString << ")" << end;
        return predicateString.str();
    }

    int getParaSize()
    {
        return parameters.size();
    }




};
#endif //CS236PROJ1_PREDICATE_H