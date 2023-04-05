//
// Created by elton on 3/7/2023.
//

#ifndef MAIN_CPP_SCHEME_H
#define MAIN_CPP_SCHEME_H
#include <string>
#include <vector>
# include <sstream>

using namespace std;

class Scheme : public vector<string> {
public:

    Scheme(vector<string> names) : vector<string>(names) { }// this is the names of the parameters of the scheme

string toString(const Scheme scheme)
{
        stringstream out;
    for (int i = 0; i < static_cast<int>(scheme.size()); ++i)
    {
        out << scheme.at(i);
        if(i != static_cast<int>(scheme.size()-1))
        {
            out << " ";
        }
    }
    return out.str();
}

};


#endif //MAIN_CPP_SCHEME_H
