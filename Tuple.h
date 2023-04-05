//
// Created by elton on 3/7/2023.
//

#ifndef MAIN_CPP_TUPLE_H
#define MAIN_CPP_TUPLE_H
#include <vector>
#include <string>
#include <sstream>
#include "Scheme.h"

using namespace std;

class Tuple : public vector<string> {

public:

    Tuple(vector<string> values) : vector<string>(values) { }

    string toString(const Scheme& scheme) const {
        const Tuple& tuple = *this;
        stringstream out;
//        cout << "TC 1 -- size " << scheme.size() << endl;
        // fix the code to print "name=value" pairs
        for(int i = 0; i < static_cast<int>(scheme.size());i++)
        {
            out << scheme.at(i);

            out << "=";
            out << tuple.at(i);
//            cout << scheme.at(i) << endl;
            if( i !=static_cast<int>(scheme.size()-1))
                out << ", ";
        }
//        cout << "TC 2" << endl;
        return out.str();
    }


};
#endif //MAIN_CPP_TUPLE_H
