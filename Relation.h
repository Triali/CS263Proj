//
// Created by elton on 3/7/2023.
//

#ifndef MAIN_CPP_RELATION_H
#define MAIN_CPP_RELATION_H

#include <set>
#include <iostream>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation
{

private:

    string name;
    Scheme scheme;
    vector<int> typeCode;
    int typeCodeType;
    set<Tuple> tuples;

public:

    Relation(const string &name, const Scheme &scheme)
            : name(name), scheme(scheme)
    {}

    int getTupleSize();

    void addTuple(const Tuple &tuple);

    string NameSchemetoString();

    string toString() const;

    string toFullString() const;

    string getName() const;

    void changeName(string NewName);
    string getSchemeStr();

    vector<string> getScheme();

    vector<int> getTypeCode();

    Relation select(Relation query);

    Relation selectConstant(int index, const string &value) const;

    Relation selectVar(int index1, int index2);

    Relation rename(Scheme newScheme);

    void setTypeCode();

    int getTypeCodeType();

    string typeCodetoString();

    static bool joinable(const Scheme &leftScheme, const Scheme &rightScheme,
                         const Tuple &leftTuple, const Tuple &rightTuple);

    Relation project(Scheme newScheme);

    bool isEmpty();

    string printNewTuples(Relation newRel);

    Relation join(const Relation &right);

    Scheme joinScheme(const Scheme rightScheme);

    set<Tuple> getTuples();


    Tuple joinTuple(const Scheme &leftScheme, const Scheme &rightScheme,
                    const Tuple &leftTuple, const Tuple &rightTuple);

    Tuple UnionTuple(const Tuple &leftTuple, const Tuple &rightTuple);

    bool canJoinSchemes(const Scheme &leftScheme, const Scheme &rightScheme);
    //return true if one element of the schemes is common between the 2, means they have the possiblity of bing joined
};

#endif //MAIN_CPP_RELATION_H
