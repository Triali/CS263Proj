//
// Created by elton on 1/24/2023.
//

#ifndef CS236LAB1_SCANNER_H
#define CS236LAB1_SCANNER_H
using namespace std;

#include <string>
#include "Token.h"
#include <vector>
#include <cctype>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>


class Scanner
{
private:
    string input;
    int line = 1;
    string value;
    int toeknCount = 0;
    vector<Token> tokenList;
    map<char, int>::iterator it;
    map<char, int> charMap
            {
                    {',',  1},
                    {'.',  2},
                    {'?',  3},
                    {'(',  4},
                    {')',  5},
                    {':',  6},//colon and colon dash
                    {'*',  7},
                    {'+',  8},
                    {'S',  9},
                    {'F',  10},
                    {'R',  11},
                    {'Q',  12},
                    {'\'', 13},
                    {'#',  14}
            };


public:
    Scanner(const string &input) : input(input)
    {}

    void RemoveWhitespace()
    {
        while (isspace(input.at(0)))
        {
            if (input.at(0) == '\n')
            {
                line++;
            }

            input.erase(input.begin(), input.begin() + 1);
            if(input.empty())
            {
                return;
            }
        }
    }

    Token scanToken()
    {
        int charNum;


// cout << charMap.find(input.at(0)) << endl;
        it = charMap.find(input.at(0));// find values related to charactor at start of string

        if (it != charMap.end())
        {
            charNum = charMap.at(input.at(0));
        }
        else
        {
            charNum = 16;
        }
//        cout << "state: " << charNum << endl;
        switch (charNum)
        {
            case 1://,
            {
                input.erase(0, 1);
//                cout << input << endl;
                return Token(COMMA, ",", line);
                break;
            }

            case 2://.
            {
                input.erase(0, 1);
//                cout << input << endl;
                return Token(PERIOD, ".", line);
                break;
            }

            case 3://?
            {
                input.erase(0, 1);
//                cout << input << endl;
                return Token(Q_MARK, "?", line);
                break;
            }

            case 4://(
            {
                input.erase(0, 1);
//                cout << input << endl;
                return Token(LEFT_PAREN, "(", line);
                break;
            }

            case 5://)
            {
                input.erase(0, 1);
//                cout << input << endl;
                return Token(RIGHT_PAREN, ")", line);
                break;
            }

            case 6://:/:-
            {
                if (input.substr(0, 2) == ":-")
                {
                    input.erase(0, 2);
//                    cout << input << endl;
                    return Token(COLON_DASH, ":-", line);
                }
                else
                {
                    input.erase(0, 1);
                    return Token(COLON, ":", line);
                }
                break;
            }

            case 7://*
            {
                input.erase(0, 1);
//                cout << input << endl;
                return Token(MULTIPLY, "*", line);
                break;
            }

            case 8://+
            {
                input.erase(0, 1);
//                cout << input << endl;
                return Token(ADD, "+", line);
                break;
            }

            case 9://schemes
            {
                int endInd = FindEndIdx();
//                cout  << endInd << endl;
//                cout << "input.substr(0, 7)" << input.substr(0, 7) << endl;
                if (input.substr(0, endInd) == "Schemes")
                {

                    input.erase(0, 7);
                    return Token(SCHEMES, "Schemes", line);
                }
                else
                {
                    return IDToken();
                }
            }

            case 10://facts
            {
                int endInd = FindEndIdx();
                if (input.substr(0, endInd) == "Facts")
                {
                    input.erase(0, 5);
                    return Token(FACTS, "Facts", line);
                }
                else
                {
                    return IDToken();
                }
            }

            case 11://rules
            {
                int endInd = FindEndIdx();
                if (input.substr(0, endInd) == "Rules")
                {
                    input.erase(0, 5);
                    return Token(RULES, "Rules", line);
                }
                else
                {
                    return IDToken();
                }
            }

            case 12://Queries
            {
                int endInd = FindEndIdx();
                if (input.substr(0, endInd) == "Queries")
                {
                    input.erase(0, 7);
                    return Token(QUERIES, "Queries", line);
                }
                else
                {
                    return IDToken();
                }
            }

            case 13://strings
            {
                if(input.size()==1)
                    return (undefToken(input));
                int i = 1;
                while (input.at(i) != '\'')
                {
                    if(i == static_cast<int>(input.size())-1)
                        return(undefToken(input));
                    i++;
                    int dInd = input.find("\'\'",i);
                    int sInd = input.find("\'",i);
//                    cout << "dInd " << dInd << endl;
//                    cout << "Size : " << input.size() << endl;
                    if(dInd == sInd)
                    {
                        if (dInd != static_cast<int>(string::npos))
                        {
                            int diff = input.size()-dInd;
                            if (diff == 3)
                            {
                                i=dInd + 3;
                            }
                            if ( diff > 3)
                            {
                                i=dInd + 3;

                            }
                            if (diff < 3)
                            {
                                i = dInd;
                            }
                        }
                        else
                        {
                            if (sInd != static_cast<int>(string::npos))
                            {
                                i=sInd;
                            }
                        }

//                        cout << "D: " << diff << endl;
                    }
//                    cout << "I: " << i << endl;
                }
                value = input.substr(0, i+1);
                input.erase(0, i+1);
                return Token(STRING, value, line);
            }

            case 14://comments
            {
                if (input.at(1) == '|')
                {
                    int endIdx = input.find("|#");
                    if (endIdx == static_cast<int>(string::npos))
                    {
                        value  = input;
                        return undefToken(value);
                    }
                    else
                    {
                        value = input.substr(0, endIdx + 2);
                        input.erase(0, endIdx + 2);
//                        cout << input << endl;
                        return Token(COMMENT, value, line);
                    }
                }
                else
                {
                    int endIdx = input.find('\n');
                    if (endIdx == static_cast<int>(string::npos))
                    {
                        value = input;
                    }
                    else
                    {
                        value = input.substr(0, endIdx);
                    }
                    input.erase(input.begin(), input.begin() + endIdx);
//                        cout << input << endl;
                    return Token(COMMENT, value, line);
                }
            }


            case 15://end of file
            {
                return Token(ENDFILE, "", line);
            }

            case 16:// make an ID function
            {

                return IDToken();
                break;
            }

            case 17://undefined
            {
                value = input.at(0);
                input.erase(0, value.size());
                return Token(UNDEFINED, value, line);
            }

            default:
                return undefToken("");

        }
    }

    Token IDToken()
    {
        int endIdx = FindEndIdx();
        if (endIdx == static_cast<int>(string::npos))
        {
            value = input;
        }
        else
        {
            value = input.substr(0, endIdx);
        }
        if (!isalpha(input.at(0)))
        {
            value = input.at(0);
            return undefToken(value);
        }

        input.erase(0, value.size());
        return Token(ID, value, line);
    }

    Token undefToken(string value)
    {
        int i = 0;
        int startline = line;
        while(i != static_cast<int>(string::npos))
        {

            i = value.find("\n",i+1);
            if (i != static_cast<int>(string::npos))
            {
                line++;
            }
        }
        input.erase(0, value.size());
        return Token(UNDEFINED, value, startline);
    }

    string GetInput()
    {
        return input;
    }

    void scanAll()
    {
        while (input.size() != 0)
        {
            RemoveWhitespace();
            if(input.size() != 0)
            {
                tokenList.push_back(scanToken());
                toeknCount++;
            }
        }
        tokenList.push_back(Token(ENDFILE, "", line));
        toeknCount++;
    }

    void PrintTokenVector()
    {
        for (int i = 0; i < static_cast<int>(tokenList.size()); ++i)
        {
            cout << tokenList.at(i).toString() << endl;
        }
    }

    string TokenVectorToString()
    {
        stringstream tokenStr;
        for (int i = 0; i < static_cast<int>(tokenList.size()); ++i)
        {
            tokenStr << tokenList.at(i).toString() << endl;
        }
        tokenStr << "Total Tokens = " << getTokenCount() << endl;
        return tokenStr.str();

    }

    int FindEndIdx( vector<char> symList)
    {
        // " " , . ? ( ) : * + # "\'"
        int endInx = -1;
        for (int i = 0; i < static_cast<int>(symList.size()); ++i)
        {
            int ind = findEndID(symList.at(i));
//            cout << "char: " << symList.at(i) << endl;
//            cout << "ind: "<< ind << endl << endl;
            if (endInx == -1)
            {
                endInx = ind;
            }
            else
            {
                if ((ind < endInx) && (ind > 0))
                {
                    endInx = ind;
                }
            }

        }
//        cout << "index: " << endInx << endl;
        return endInx;

    }

    int FindEndIdx()
    {
        vector<char> symList = {' ', ',', '.', '?', '(', ')', ':', '*', '+', '#', '\'', '\n'};
        // " " , . ? ( ) : * + # "\'"
        int endInx = -1;
        for (int i = 0; i < static_cast<int>(symList.size()); ++i)
        {
            int ind = findEndID(symList.at(i));
//            cout << "char: " << symList.at(i) << endl;
//            cout << "ind: "<< ind << endl << endl;
            if (endInx == -1)
            {
                endInx = ind;
            }
            else
            {
                if ((ind < endInx) && (ind > 0))
                {
                    endInx = ind;
                }
            }

        }
//        cout << "index: " << endInx << endl;
        return endInx;

    }

    int findEndID(char item)
    {
//        cout << "char: " << item << endl;
        int idx = input.find(item);
        if (idx == static_cast<int>(string::npos))
        {
            idx = -1;
        }
//        cout << "index: " << idx << endl;
        return idx;
    }

    int getTokenCount()
    {
        return toeknCount;
    }

    void PrintOutput()
    {
//        cout << "VS " << tokenList.size() << endl;
        scanAll();
//        cout << "VS " << tokenList.size() << endl;
        PrintTokenVector();
//        for (int i; i < tokenList.size(); i++)
//        {
//            cout << tokenList.at(i).toString() << endl;
//        }
        cout << "Total Tokens = " << getTokenCount() << endl;
    }



    vector<Token> getTokenList()
    {
        return tokenList;
    }

    void GetFile(string fileName)
    {
        ifstream myfile;
        myfile.open(fileName);
        while (!myfile.eof())
        {
            string sub;
            getline(myfile, sub);//make a loop for reading whole file
//        cout << sub << endl;
            input = input + sub + "\n";
        }
        input.pop_back();
        myfile.close();
    }

};


#endif //CS236LAB1_SCANNER_H
