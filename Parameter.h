#ifndef CS236PROJ1_PARAMETER_H
#define CS236PROJ1_PARAMETER_H

#include <string>
using namespace std;

class Parameter
{
private:
    //store the vales of the parameter
    string value;

public:
    //contructor
    Parameter(string value)
    {
        this-> value = value;
    }
//return value
    string getValue()
    {
        return value;
    }

};
#endif //CS236PROJ1_PARAMETER_H