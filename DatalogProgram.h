//
// Created by elton on 2/10/2023.
//

#ifndef CS236PROJ1_DATALOGPROGRAM_H
#define CS236PROJ1_DATALOGPROGRAM_H

#include "Rule.h"
#include "Predicate.h"
#include <set>
#include "Database.h"

using namespace std;

class DatalogProgram
{
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;

    set<string> domain;
    set<string>::iterator itr;

    Database database;


public:
    vector<Predicate> getSchemeVect()
    {
        return schemes;
    }

    vector<Predicate> getFactVect()
    {
        return facts;
    }

    vector<Rule> getRuleVect()
    {
        return rules;
    }

    vector<Predicate> getQueryVect()
    {
        return queries;
    }

    void addScheme(Predicate newScheme)
    {
        schemes.push_back(newScheme);
    }

    void addFact(Predicate newFact)
    {
        facts.push_back(newFact);
        for (int i = 0; i < static_cast<int>(newFact.getParameters().size()); ++i)
        {
            domain.insert(newFact.getParameters().at(i).getValue());
        }

    }

    void addRule(Rule newRule)
    {
        rules.push_back(newRule);
    }

    void addQuery(Predicate newQuery)
    {
        queries.push_back(newQuery);
    }

    string DatalogProgramToString()
    {
        stringstream dpString;
        dpString << "Schemes(" << static_cast<int>(schemes.size()) << "):" << endl;
        dpString << PredVectToString(schemes);

        dpString << "Facts(" << static_cast<int>(facts.size()) << "):" << endl;
        dpString << PredVectToString(facts);

        dpString << "Rules(" << static_cast<int>(rules.size()) << "):" << endl;
        dpString << RuleVectToString(rules);

        dpString << "Queries(" << static_cast<int>(queries.size()) << "):" << endl;
        dpString << PredVectToString(queries);

        dpString << "Domain(" << static_cast<int>(domain.size()) << "):" << endl;
        dpString << StringSetToString(domain);

        return dpString.str();
    }

    string PredVectToString(vector<Predicate> predVect)
    {
        stringstream predString;
        for (int i = 0; i < static_cast<int>(predVect.size()); ++i)
        {
            predString << predVect.at(i).PredicateToString()<< endl;
        }
        return predString.str();
    }

    string RuleVectToString(vector<Rule> ruleVect)
    {
        stringstream ruleString;
        for (int i = 0; i < static_cast<int>(ruleVect.size()); ++i)
        {
            ruleString << ruleVect.at(i).RuleToString() << endl;
        }
        return ruleString.str();
    }

    string StringSetToString(set<string> sSet)
    {
        stringstream setString;
        for (itr = sSet.begin(); itr != sSet.end(); itr++) {
            setString << "  " << *itr << endl;
        }
        return setString.str();
    }



    void PrintDatabase()
    {
        cout << database.toStringRelations() << endl;
    }





    string toStringDatabase()
    {
        return database.toStringRelations();
    }


};

#endif //CS236PROJ1_DATALOGPROGRAM_H
