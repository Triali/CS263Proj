//
// Created by elton on 4/3/2023.
//
#include "Relation.h"


int Relation::getTupleSize()
{
    return tuples.size();
}

void Relation::addTuple(const Tuple &tuple)
{
    tuples.insert(tuple);
}

string Relation::NameSchemetoString()
{
    stringstream out;
//cout << tuples.size() << endl;
    out << name << "(";
    for (int i = 0; i < static_cast<int>(scheme.size()); ++i)
    {
        out << scheme.at(i);
        if (i != static_cast<int>(scheme.size() - 1))
            out << ",";

    }
    out << ")?";
    return out.str();
}

string Relation::toString() const
{
    stringstream out;
//cout << tuples.size() << endl;
    for (auto &tuple: tuples)

        out << "  " << tuple.toString(scheme) << endl;
    return out.str();
}

string Relation::toFullString() const
{
    stringstream out;
//cout << tuples.size() << endl;
    out << name << ":";
    for (int i = 0; i < static_cast<int>(scheme.size()); ++i)
    {
        out << scheme.at(i) << " ";

    }
    out << endl;
    for (auto &tuple: tuples)

        out << tuple.toString(scheme) << endl;
    return out.str();
}

string Relation::getName() const
{
    return name;
}

void Relation::changeName(string NewName)
{
    name = NewName;
}

string Relation::getSchemeStr()
{
    stringstream schemelist;
    for (int i = 0; i < static_cast<int>(scheme.size()); i++)
    {
        schemelist << scheme.at(i) << " ";
    }
    return schemelist.str();
}

vector<string> Relation::getScheme()
{
    return scheme;
}

vector<int> Relation::getTypeCode()
{
    return typeCode;
}

Relation Relation::select(Relation query)
{
//        cout << query.toFullString() << endl;
    Scheme qScheme = query.getScheme();
    Relation result(name, scheme);
    for (auto index: tuples)
        result.addTuple(index);

//        cout << "starter" << endl << result.toFullString() << endl;


    vector<int> types;
    // -1 is a constant
    // variable is the index
    //repeated variable is index of first use
    for (int i = 0; i < static_cast<int>(qScheme.size()); i++)
    {
//            cout << "current scheme" << endl;
//            cout << qScheme.at(i) << endl;
        if (qScheme.at(i).at(0) == '\'')
        {
//                cout << "found Constant" << endl;
            types.push_back(-1);
            result = result.selectConstant(i, qScheme.at(i));
//                cout << result.toFullString() << endl;
        }
        else
        {
//                cout << "found variable" << endl;
            bool added = false;
            for (int j = 0; j < i; ++j)
            {
                if (types.at(j) != -1 && qScheme.at(i) == qScheme.at(j))
                {
//                        cout << "found double variable" << endl;
//                        cout <<qScheme.at(i) <<"==" <<qScheme.at(j) << endl;
//                        cout << i << "==" << j << endl;
                    types.push_back(j);
                    result = result.selectVar(i, j);
//                        cout << result.toFullString() << endl;
                    added = true;
                    break;
                }


            }
            if (!added)
            {
                types.push_back(i);

            }

        }

    }
//        typeCode = types;
    vector<int> indexes;
    for (int i = 0; i < static_cast<int>(types.size()); ++i)
    {
//            cout << types.at(i) << " ";
        indexes.push_back(i);
    }
//        cout << endl;
//        cout << "final" << endl << result.toFullString();

    return result;
}

Relation Relation::selectConstant(int index, const string &value) const
{
//        cout << "running Select constant" << endl;
    Relation result(name, scheme);
    for (auto &tuple: tuples)
    {
//            cout << value << "=-=" << tuple.at(index) << endl;
        if (value == tuple.at(index))
            result.addTuple(tuple);

    }

    return result;
}

Relation Relation::selectVar(int index1, int index2)
{
//        cout << "Running select Variable" << endl;
    Relation result(name, scheme);
    for (auto &tuple: tuples)
    {
        if (tuple.at(index1) == tuple.at(index2))
            result.addTuple(tuple);
    }

    // add tuples to the result if they meet the condition
    return result;
}

Relation Relation::rename(Scheme newScheme)
{
//        cout << "running rename" << endl;
    Relation result(name, newScheme);
    for (auto index: tuples)
        result.addTuple(index);
//        cout << "starter" << endl << result.toFullString() << endl;
    return result;
}

void Relation::setTypeCode()
{
    bool hasVar = false;
    bool hasDVar = false;
    // -1 is a constant
    // variable is the index
    //repeated variable is index of first use
    for (int i = 0; i < static_cast<int>(scheme.size()); i++)
    {

//            cout << "current scheme" << endl;
//            cout << qScheme.at(i) << endl;
        if (scheme.at(i).at(0) == '\'')
        {
//                cout << "found Constant" << endl;
            typeCode.push_back(-1);
//                cout << result.toFullString() << endl;
        }
        else
        {
            hasVar = true;
//                cout << "found variable" << endl;
            bool added = false;
            for (int j = 0; j < i; ++j)
            {
                if (typeCode.at(j) != -1 && scheme.at(i) == scheme.at(j))
                {
//                        cout << "found double variable" << endl;
                    typeCode.push_back(j);
//                        cout << result.toFullString() << endl;
                    added = true;
                    hasDVar = true;
                    break;
                }
            }
            if (!added)
            {
                typeCode.push_back(i);
            }
        }
    }
    if (hasDVar)
    {
        typeCodeType = 3;
    }
    else if (hasVar)
    {
        typeCodeType = 2;
    }
    else
    {
        typeCodeType = 1;
    }
}

int Relation::getTypeCodeType()
{
    return typeCodeType;
}

string Relation::typeCodetoString()
{
    stringstream tcStr;
    for (int i = 0; i < static_cast<int>(typeCode.size()); ++i)
    {
        tcStr << typeCode.at(i) << " ";
    }
    tcStr << endl;
    return tcStr.str();
}

bool Relation::joinable(const Scheme &leftScheme, const Scheme &rightScheme,
                        const Tuple &leftTuple, const Tuple &rightTuple)
{
    //    The 'joinable' function is given the scheme and a tuple
//      from the left relation of the join and the scheme and a
//      tuple from the right relation of the join.
//    The 'joinable' function returns 'true' if the two tuples
//      should be combined to form a tuple in the result of the join.

    bool canJoinOne = false;
    bool canJoinAll = true;

//        tuple are joinable if:
//        scheme names match
//        values for matching scheme names are the same

// loop of left scheme tuple
    for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++)
    {
        const string &leftName = leftScheme.at(leftIndex);
        const string &leftValue = leftTuple.at(leftIndex);
//            cout << "left name: " << leftName << " value: " << leftValue << endl;

        // loop of right scheme tuple
        for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++)
        {
            const string &rightName = rightScheme.at(rightIndex);
            const string &rightValue = rightTuple.at(rightIndex);
//                cout << "right name: " << rightName << " value: " << rightValue << endl;

//
//                cout << leftName << "::" << rightName << endl;
//                cout << leftValue << "::" << rightValue << endl;
            if (leftName == rightName)
            {
                if (leftValue == rightValue)
                {
                    canJoinOne = true;
                }
                else
                {
                    canJoinAll = false;
                }
            }
        }

    }
    if (canJoinOne)
    {
        if (canJoinAll)
        {
            return true;
        }
    }


    return false;
}

Relation Relation::project(Scheme newScheme)
{

    //it can move columes
    Relation result(name, newScheme);
    vector<int> matches;
    for (int i = 0; i < static_cast<int>(newScheme.size()); ++i)
    {
        for (int j = 0; j < static_cast<int>(scheme.size()); ++j)
        {
//                cout << i << "=-=" << j << endl;
            if (newScheme.at(i) == scheme.at(j))
            {
//                    cout << "match "<< j << "//" << newScheme.at(i) <<"=="<< scheme.at(j)<<endl;
                matches.push_back(j);
            }
        }
    }
//        for (int i = 0; i < matches.size(); ++i)
//        {
//            cout << matches.at(i) << " ";
//        }
//        cout << endl;
    vector<int> keepers;
    for (int i = 0; i < static_cast<int>(matches.size()); ++i)
    {
//            cout << matches.at(i)<<":" <<scheme.at(matches.at(i)) << " ";
        bool isIn = false;
        for (int j = 0; j < i; ++j)
        {
            if (scheme.at(matches.at(i)) == scheme.at(matches.at(j)))
            {
                isIn = true;
            }
        }
        if (!isIn)
            keepers.push_back(matches.at(i));
    }
//        cout << endl;

//        cout << "keepers"<< endl;
//        for (int i = 0; i < static_cast<int>(keepers.size()); ++i)
//        {
//            cout << keepers.at(i) << " ";
//        }
//        cout << "//" << endl;

    for (auto tuple: tuples)
    {
        vector<string> newTupleSet;
        for (int count = 0; count < static_cast<int>(keepers.size()); ++count)
        {
            int i = keepers.at(count);
            newTupleSet.push_back(tuple.at(i));
        }
        Tuple newTuple(newTupleSet);
        result.addTuple(newTuple);
    }


    return result;

}

bool Relation::isEmpty()
{
    if (tuples.empty())
        return true;
    return false;
}

string Relation::printNewTuples(Relation newRel)
{
    stringstream out;
    for (Tuple t: newRel.getTuples())
    {
        if (tuples.find(t) == tuples.end())
        {
            out << "  " << t.toString(scheme) << endl;
        }
    }
    return out.str();
}

Relation Relation::join(const Relation &right)
{
//        cout << "running Union" << endl;
    const Relation &left = *this;
    // create new scheme
    Scheme newScheme = joinScheme(right.scheme);
    // Prints the new scheme
    //        for (auto ID:newScheme)
//        {
//            cout << ID << " ";
//        }
//        cout << endl;


    // create a new relation with the same name and a new scheme
    Relation result(name, newScheme);


    // iterate over all tuples


// Loop over the tuples in the left relation
    if (canJoinSchemes(scheme, right.scheme))
    {
        for (const Tuple &leftTuple: left.tuples)
        {
            // prints the tuples in the left relation
//            cout << "left tuple: " << leftTuple.toString(left.scheme) << endl;
            for (const Tuple &rightTuple: right.tuples)
            {
                // prints the tuples in the right relation
//                cout << "right tuple: " << rightTuple.toString(right.scheme);
                if (joinable(scheme, right.scheme, leftTuple, rightTuple))
                {
//                    cout << "  joinable" << endl;
                    result.addTuple(joinTuple(scheme, right.scheme, leftTuple, rightTuple));
//                cout << result.toFullString() << endl;

                }
                else
                {
//                    cout << "  not joinable";
                }
//                cout << endl;
            }
        }
//    cout << result.toFullString() << endl;
    }
    else
    {
        for (const Tuple &leftTuple: left.tuples)
        {
            for (const Tuple &rightTuple: right.tuples)
            {
//                cout << "running Union" << endl;
                result.addTuple(UnionTuple(leftTuple, rightTuple));
            }
        }

    }
//Loop over the tuples in the right relation
//        cout << result.toFullString() << endl;
    // add code to complete the join operation
    return result;
}

Scheme Relation::joinScheme(const Scheme rightScheme)
{

    Scheme newScheme = scheme;
    for (int i = 0; i < static_cast<int>(rightScheme.size()); ++i)
    {
        bool isInScheme = false;
        for (int j = 0; j < static_cast<int>(newScheme.size()); ++j)
        {
            if (newScheme.at(j) == rightScheme.at(i))
                isInScheme = true;
        }
        if (!isInScheme)
        {
            newScheme.push_back(rightScheme.at(i));
        }


    }
    return newScheme;
}

set<Tuple> Relation::getTuples()
{
    return tuples;
}


Tuple Relation::joinTuple(const Scheme &leftScheme, const Scheme &rightScheme,
                          const Tuple &leftTuple, const Tuple &rightTuple)
{
    vector<string> tupID;
    Tuple newTuple = leftTuple;
//        we loop through the right scheme
    for (int i = 0; i < static_cast<int>(rightScheme.size()); ++i)
    {
        //        we assume that each item in the right scheme is not in the left scheme at first.
        bool isIn = false;
        for (int j = 0; j < static_cast<int>(leftScheme.size()); ++j)
        {
            if (rightScheme.at(i) == leftScheme.at(j))
            {
                isIn = true;
            }
        }
        if (!isIn)
        {
            newTuple.push_back(rightTuple.at(i));
        }


    }

// cout << "new tuple: " << endl<< newTuple.toString(newTuple) << endl;
    return newTuple;
}

Tuple Relation::UnionTuple(const Tuple &leftTuple, const Tuple &rightTuple)
{
    vector<string> tupID;
//        we loop through the right scheme
    for (int i = 0; i < static_cast<int>(leftTuple.size()); ++i)
    {
        tupID.push_back(leftTuple.at(i));
    }
    for (int i = 0; i < static_cast<int>(rightTuple.size()); ++i)
    {
        tupID.push_back(rightTuple.at(i));
    }
    Tuple newTuple = Tuple(tupID);
    return newTuple;
}

bool Relation::canJoinSchemes(const Scheme &leftScheme, const Scheme &rightScheme)
{
    for (int i = 0; i < static_cast<int>(leftScheme.size()); i++)
    {

        // loop of right scheme tuple
        for (int j = 0; j < static_cast<int>(rightScheme.size()); j++)
        {
//            cout << leftScheme.at(i) << "::" <<  rightScheme.at(j) << endl;
            if (leftScheme.at(i) == rightScheme.at(j))
            {
//                cout << "can join schemes" << endl;
                return true;
            }
        }
    }
    return false;
}




