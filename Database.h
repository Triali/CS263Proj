//
// Created by elton on 3/13/2023.
//

#ifndef MAIN_CPP_DATABASE_H
#define MAIN_CPP_DATABASE_H

#include "Relation.h"
#include "iostream"
#include <set>


using namespace std;


class Database
{

private:

    vector<Relation> relations;


public:
//initalizer
    Database() = default;

    Database(vector<Predicate> schemes, vector<Predicate> facts)
    {
        vector<string> names;
        vector<vector<string>> parameters;
        for (int i = 0; i < static_cast<int>(schemes.size()); i++)
        {
            names.push_back(schemes.at(i).getName());
            parameters.push_back(schemes.at(i).getParameterNames());
        }
        for (int i = 0; i < static_cast<int>(schemes.size()); ++i)
        {
            Scheme scheme(parameters.at(i));
            Relation relation(names.at(i), scheme);
            addRelation(relation);
        }
        addFacts(facts);
    }

    string EvaluateRules(vector<Rule> rules)
    {
        stringstream write;
        write << "Rule Evaluation" << endl;
                cout << "print Database(Datalog C command)" << endl;
        cout << toStringRelations();
// run until the vector of relations does not change does not change
        int iter = 0;
        vector<int> sizes = RelationsSizes();

        bool isSameSize = false;
        while (!isSameSize)
        {
//            cout << "pass: " << iter << endl;
            isSameSize = true;

//            cout << "running evaluating rules" << endl;
//             evaulate each rule once
            for (int i = 0; i < static_cast<int>(rules.size()); ++i)
            {
                write << rules.at(i).RuleToStringQ() << endl;
                //cout << "==================" << endl;
                Relation temp = evaluateRule(rules.at(i));

                int oldSize;
                int newSize;
                for (int j = 0; j < static_cast<int>(relations.size()); ++j)
                {
//                     finds the right relation
                    if (temp.getName() == relations.at(j).getName())
                    {
                        Scheme newScheme = relations.at(j).getScheme();
//                        cout << relations.at(j).getSchemeStr() << endl;
//cout << "(DB 77) " << endl<< temp.toFullString() << endl;
                        temp = temp.rename(newScheme);
                        write << relations.at(j).printNewTuples(temp);
                        oldSize = relations.at(j).getTupleSize();
                        Union(temp);
                        newSize = relations.at(j).getTupleSize();
                    }
                }

//                cout << oldSize << "::" << newSize << endl;
                if (oldSize != newSize)
                {
                    isSameSize = false;

//                    write << temp.toString();
                }
                if(rules.size() == 1)
                {
                    isSameSize = true;
                }


            }
            //repeat until relations and NewRelations are the same size
            sizes = RelationsSizes();
            iter++;
        }

        write << endl << "Schemes populated after " << iter << " passes through the Rules." << endl << endl;
        return write.str();
    }

    string ProcessQueries(vector<Predicate> queries)
    {
        stringstream out;
        out << "Query Evaluation" << endl;
//        cout << "processing Queries" << endl;
        for (auto query: queries)
        {
            Predicate Q = query;
            Relation relQ = Q.PredtoRel();
//        cout << "print Query as Relation" << endl << relQ.toFullString() << endl;
            relQ.setTypeCode();
//        cout << "print query as type code" << endl << relQ.typeCodetoString()<< endl << "type: " << relQ.getTypeCodeType();
            Relation result = select(relQ);
            bool Qtrue = !result.isEmpty();

            if (relQ.getTypeCodeType() > 1)
            {
                //modify scheme
                Scheme schemeC = result.getScheme();
                Scheme schemeQ = relQ.getScheme();
                for (int i = 0; i < static_cast<int>(schemeC.size()); i++)
                {
                    if (schemeQ.at(i).at(0) == '\'')
                    {
                        schemeQ.at(i) = schemeC.at(i);
                    }
                }
                result = result.rename(schemeQ);

                vector<int> keepers;
                for (int i = 0; i < static_cast<int>(relQ.getTypeCode().size()); ++i)
                {
                    if ((relQ.getTypeCode().at(i)) == i)
                    {
                        keepers.push_back(i);
                    }
                }
                vector<string> newScheme;


                for (int i = 0; i < static_cast<int>(keepers.size()); ++i)
                {
                    newScheme.push_back(relQ.getScheme().at(keepers.at(i)));
                }


                Scheme newQscheme(newScheme);

//                cout << "Qscheme for Projection" << endl << "size" << static_cast<int>(newScheme.size()) << endl;
//                for (int i = 0; i < static_cast<int>(newScheme.size()); ++i)
//                {
//                    cout << newScheme.at(i)<< " ";
//                }

                result = result.project(newQscheme);
            }
            out << relQ.NameSchemetoString() << " ";
            if (Qtrue)
                out << "Yes(" << result.getTupleSize() << ")" << endl;
            else
                out << "No" << endl;
            if (relQ.getTypeCodeType() != 1)
                out << result.toString();


        }
        return out.str();
    }

    Relation select(Relation query)
    {
        //returns a relation with the same name and Scheme
        // the tuples have been selected based on the query passed in
//        cout << "Running Database Select" << endl;
        Relation result(query.getName(), query.getScheme());
        for (int i = 0; i < static_cast<int>(relations.size()); ++i)
        {
            if (query.getName() == relations.at(i).getName())
            {
//                cout << relations.at(i).toFullString() << endl;
                result = relations.at(i).select(query);
            }

        }
        return result;
    }

    void addRelation(Relation &relation)
    {
//        cout << "adding relation" << endl;
        relations.push_back(relation);
    }

    string toStringRelations()
    {
        stringstream rList;
        for (Relation i: relations)
        {
            rList << i.getName() << ": " << i.getSchemeStr() << endl;
            rList << i.toString() << endl;
        }
        return rList.str();
    }

    void addFacts(vector<Predicate> facts)
    {
        for (int i = 0; i < static_cast<int>(relations.size()); i++)
        {

            string rName = relations.at(i).getName();
            for (int j = 0; j < static_cast<int>(facts.size()); ++j)
            {
                string name = facts.at(j).getName();

                if (name == rName)
                {
                    vector<string> parameters = facts.at(j).getParameterNames();
                    Tuple tuple = Tuple(parameters);
                    relations.at(i).addTuple(tuple);

                }
            }
//            cout << i.toString() << endl;
        }


    }

    Relation rename(Relation newSRel)
    {
        Relation result(newSRel.getName(), newSRel.getScheme());
        for (int i = 0; i < static_cast<int>(relations.size()); ++i)
        {
            if (newSRel.getName() == relations.at(i).getName())
            {
//                cout << relations.at(i).toFullString() << endl;
                result = relations.at(i).rename(newSRel.getScheme());
            }
        }
        return result;

    }

    Relation project(Relation newRel)
    {
        Relation result(newRel.getName(), newRel.getScheme());// temp
        for (int i = 0; i < static_cast<int>(relations.size()); ++i)
        {
            if (newRel.getName() == relations.at(i).getName())
            {
//                cout << relations.at(i).toFullString() << endl;
                result = relations.at(i).project(newRel.getScheme());
            }
        }

        return result;

    }

    Relation evaluateRule(Rule rule)
    {
        // get name
        string name = rule.getHeadPredicate().getName();
        Relation result = rule.getHeadPredicate().PredtoRel();
        vector<Relation> arguments;
        //evaluate predicates on the right hand side of the rule like they were queries, save as relations
        // make a evaulateQuery function that will evaluate one query and return a relation
        for (int i = 1; i < static_cast<int>(rule.getPredicates().size()); ++i)
        {
            Relation ruleQ = EvaluateQuery(rule.getPredicates().at(i));
//            cout << "(DB 270)" << endl << ruleQ.toFullString();
            arguments.push_back(ruleQ);
        }
        //join relations
        while (arguments.size() != 1)
        {
            int S = arguments.size();
//            cout << S<< endl;
//            cout << arguments.at(S-2).toFullString() << endl;
//            cout << arguments.at(S-1).toFullString() << endl;
            arguments.at(S - 2) = arguments.at(S - 2).join(arguments.at(S - 1));
//            cout << arguments.at(S-2).toFullString() << endl;
            arguments.pop_back();
        }
        Relation RelQ = arguments.at(0);
        //project the columns in the head predicate
        result = RelQ.project(rule.getHeadPredicate().PredtoRel().getScheme());

//        cout << result.toFullString() << endl;
        //rename relation, change name to name of head prediate

        result.changeName(name);
//        cout << "(DB 292)" << endl << result.toFullString() << endl;
        // union with relation of rules

        return result;
    }

    Relation EvaluateQuery(Predicate Query)
    {
        stringstream out;

        Relation relQ = Query.PredtoRel();
//        cout << "print Query as Relation" << endl << relQ.toFullString() << endl;
        relQ.setTypeCode();
//        cout << "print query as type code" << endl << relQ.typeCodetoString()<< endl << "type: " << relQ.getTypeCodeType();
        Relation result = select(relQ);
//        cout << "selection: " << endl << result.toFullString() << endl;
//        bool Qtrue = !result.isEmpty();


            //modify scheme
            Scheme schemeC = result.getScheme();
//            cout << "display schemes" << endl;
//            cout << schemeC.toString(schemeC) << endl;
            Scheme schemeQ = relQ.getScheme();
//            cout << schemeQ.toString(schemeQ) << endl;
            vector<string> skipSchemestr;
            for (int i = 0; i < static_cast<int>(relQ.getTypeCode().size()); ++i)
            {
                if (relQ.getTypeCode().at(i) != -1)
                {
                    skipSchemestr.push_back(schemeC.at(i));
                }
            }
            Scheme skipScheme = Scheme(skipSchemestr);
//            cout << skipScheme.toString(skipScheme) << endl;
            result = result.project(skipScheme);
//            cout << "Project " << endl << result.toFullString() << endl;


            vector<string> skipSchemestr2;
            for (int i = 0; i < static_cast<int>(relQ.getTypeCode().size()); ++i)
            {
                if (relQ.getTypeCode().at(i) != -1)
                {
                    skipSchemestr2.push_back(schemeQ.at(i));
                }
            }
            Scheme skipScheme2 = Scheme(skipSchemestr2);
            for (int i = 0; i < static_cast<int>(schemeC.size()); i++)
            {
                if (schemeQ.at(i).at(0) == '\'')
                {
                    schemeQ.at(i) = schemeC.at(i);
                }
            }
//            result = result.rename(schemeQ);
//            cout << skipScheme.toString(skipScheme2) << endl;
            result = result.rename(skipScheme2);
//            cout << "rename " << endl << result.toFullString() << endl;

            vector<int> keepers;
            for (int i = 0; i < static_cast<int>(relQ.getTypeCode().size()); ++i)
            {
                if ((relQ.getTypeCode().at(i)) == i)
                {
                    keepers.push_back(i);
                }
            }
            vector<string> newScheme;

//            cout << "finished keepers" << endl;
            for (int i = 0; i < static_cast<int>(keepers.size()); ++i)
            {
                newScheme.push_back(relQ.getScheme().at(keepers.at(i)));
            }


            Scheme newQscheme(newScheme);

//                cout << "Qscheme for Projection" << endl << "size" << static_cast<int>(newScheme.size()) << endl;
//                for (int i = 0; i < static_cast<int>(newScheme.size()); ++i)
//                {
//                    cout << newScheme.at(i)<< " ";
//                }


//            result = result.project(newQscheme);
//            cout << "newQscheme" << endl;

//        cout << relQ.NameSchemetoString() << " ";
//        if (Qtrue)
//            out << "Yes(" << result.getTupleSize() << ")" << endl;
//        else
//            out << "No" << endl;
//        if (relQ.getTypeCodeType() != 1)
//        cout << result.toString();


        return result;
    }

    vector<int> RelationsSizes()
    {
        vector<int> sizes;
        for (int i = 0; i < static_cast<int>(relations.size()); ++i)
        {
            sizes.push_back(relations.at(i).getTupleSize());
//            cout << relations.at(i).getTupleSize() << " ";
        }
//        cout << endl;
        return sizes;
    }

    void Union(Relation toAdd)
    {
        // find correct relation
        for (Relation &Rel: relations)
        {
            if (Rel.getName() == toAdd.getName())
            {
                for (Tuple t: toAdd.getTuples())
                {
                    Rel.addTuple(t);
                }
            }
        }
    }



    bool isSameSize(vector<int> sizes)
    {
        if (relations.size() != sizes.size())
            return false;
        for (int i = 0; i < static_cast<int>(relations.size()); ++i)
        {
            if (relations.at(i).getTupleSize() != sizes.at(i))
                return false;
        }
        return true;
    }


};


#endif //MAIN_CPP_DATABASE_H
