//
// Created by elton on 2/6/2023.
//

#ifndef CS236PROJ1_PARSER_H
#define CS236PROJ1_PARSER_H

#include <vector>
#include "Token.h"
#include <iostream>
#include <sstream>
#include "DatalogProgram.h"

using namespace std;

class Parser
{
private:
    vector<Token> tokens;
    Token curToken = Token(ENDFILE, "", -1);
    DatalogProgram datalogProgram2 = DatalogProgram();


public:
    Parser(const vector<Token> &tokens) : tokens(tokens)
    {}

    DatalogProgram getDatalogProgram()
    {
        return datalogProgram2;
    }
    string parse()
    {
        stringstream parseString;
        DatalogProgram datalogProgram1;
        try
        {
            datalogProgram(datalogProgram1);
        }
        catch (string msg)
        {
            parseString << msg << endl;
            return parseString.str();
//            exit(1);
        }

        parseString << "Success!" << endl;
        parseString << datalogProgram1.DatalogProgramToString();


        parseString << datalogProgram1.toStringDatabase();
        datalogProgram2 = datalogProgram1;
        return parseString.str();
    }

    TokenType tokenType()
    {
        curToken = tokens.at(0);
        return tokens.at(0).getType();
    }

    void PrintCurToken()
    {
        cout << curToken.toString() << endl;
    }

    void advanceToken()
    {
        tokens.erase(tokens.begin());
    }

    void throwError()
    {

        stringstream error;
        error << "Failure!\n  " << tokens.at(0).toString();
        throw error.str();

    }

    void match(TokenType t)
    {
//        cout << "match: " << t << endl;
//        if the current token type matches t
        while(tokenType() == COMMENT)
        {
            advanceToken();
        }
        if (t == tokenType())
        {
//        advance to the next token
            advanceToken();
        }
        else
        {
//        report a syntax error
//cout << t << endl;
//cout << curToken.getType() <<endl;
            throwError();
        }


    }

    void datalogProgram(DatalogProgram &datalogProgram)
    {
        match(SCHEMES);
        match(COLON);
//        cout << scheme().PredicateToString() << endl;
        datalogProgram.addScheme(scheme());
        schemeList(datalogProgram);

        match(FACTS);
        match(COLON);
        factList(datalogProgram);

        match(RULES);
        match(COLON);
        ruleList(datalogProgram);

        match(QUERIES);
        match(COLON);
        datalogProgram.addQuery(query());
        queryList(datalogProgram);

        match(ENDFILE);

    }

    void schemeList(DatalogProgram &dP)
    {
        if (tokenType() == ID)
        {
            dP.addScheme(scheme());
            while(tokenType() == COMMENT)
            {
                advanceToken();
            }
            schemeList(dP);
        }
        else
        {
            //lambda
        }
    }

    void factList(DatalogProgram &dP)
    {
        if (tokenType() == ID)
        {
            dP.addFact(fact());
            while(tokenType() == COMMENT)
            {
                advanceToken();
            }
            factList(dP);
        }
        else
        {
            //lambda
        }
    }

    void ruleList(DatalogProgram &dP)
    {
        if (tokenType() == ID)
        {
            dP.addRule(rule());
            while(tokenType() == COMMENT)
            {
                advanceToken();
            }
            ruleList(dP);
        }
        else
        {
            //lambda
        }
    }

    void queryList(DatalogProgram &dP)
    {
        if (tokenType() == ID)
        {
            dP.addQuery(query());
            while(tokenType() == COMMENT)
            {
                advanceToken();
            }
            queryList(dP);
        }
        else
        {
            //lambda
        }
//        cout << "finished QList" << endl;
    }

    Predicate scheme()
    {
        // RULE scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
        id();
        Predicate scheme = Predicate(curToken.getValue());
        match(LEFT_PAREN);
        scheme.AddParameter(id());
        idList(scheme);
        match(RIGHT_PAREN);
//        cout << scheme.PredicateToString() << endl;
        return scheme;
    }

    Predicate fact()
    {
        id();
        Predicate fact = Predicate(curToken.getValue());
        match(LEFT_PAREN);
        fact.AddParameter(stringM());
        stringList(fact);
        match(RIGHT_PAREN);
        match(PERIOD);
        fact.getEnd(".");
//        cout << fact.PredicateToString() << endl;
        return fact;
    }

    Rule rule()
    {

        Predicate HP = headPredicate();
        match(COLON_DASH);
        Predicate FP = predicate();
        Rule Ru = Rule(HP, FP);
        predicateList(Ru);
//        cout << Ru.RuleToString() << endl;
        match(PERIOD);
        return Ru;


    }

    Predicate query()
    {
        Predicate query = predicate();
        match(Q_MARK);
        query.getEnd("?");
//        cout << query.PredicateToString() << endl;
        return query;

    }

    Predicate headPredicate()
    {
        id();
        Predicate headPred = Predicate(curToken.getValue());
        match(LEFT_PAREN);
        headPred.AddParameter(id());
        idList(headPred);
        match(RIGHT_PAREN);
        return headPred;
    }

    Predicate predicate()
    {
        // declare predicate variable

        id();
//        PrintCurToken();
        Predicate Pred = Predicate(curToken.getValue());
        match(LEFT_PAREN);
        Pred.AddParameter(parameter());
        parameterList(Pred);
        match(RIGHT_PAREN);
//        cout << Pred.PredicateToString() << endl;
        return Pred;
    }

    void predicateList(Rule &Ru)
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            Ru.addPredicate(predicate());
            predicateList(Ru);
        }
        else
        {
            // lambda
        }
    }

    void parameterList(Predicate &Pred)
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            Pred.AddParameter(parameter());
            parameterList(Pred);
        }
        else
        {
            // lambda
        }
    }

    void stringList(Predicate &Pred)
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            Pred.AddParameter(stringM());
            stringList(Pred);
        }
        else
        {
            // lambda
        }
    }

    void idList(Predicate &Pred)
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
//            id();
            Pred.AddParameter(id());
            idList(Pred);
        }
        else
        {
            // lambda
        }
    }

    Parameter parameter()
    {

        if (tokenType() == STRING)
        {
            match(STRING);
        }
        else
        {
            match(ID);
        }


        Parameter Para = Parameter(curToken.getValue());
//        cout << Para.getValue() << endl;
        return Para;
    };

    Parameter id()
    {
        match(ID);
        Parameter Para = Parameter(curToken.getValue());
        return Para;
    }

    Parameter stringM()
    {
        match(STRING);
        Parameter Para = Parameter(curToken.getValue());
        return Para;
    }

};


#endif //CS236PROJ1_PARSER_H