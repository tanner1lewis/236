//
// Created by Tanner Lewis on 2019-01-25.
//

#ifndef SCANNER_PARSER_H
#define SCANNER_PARSER_H

#include <stdio.h>
#include <iostream>
#include "token.h"
#include "scanner.h"
#include "datalogprogram.h"

class parser {
    int tokenIndex;
    token curr_t;
    scanner& scanned;
    Predicate p;
    
public:
    parser(scanner& s);
    ~parser(){};
    datalog DL;
    
    void parse();
    void match(tokenType t);
    token getToken();
    void datalogProgram();
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    Predicate headPredicate();
    Predicate predicate();
    vector<Predicate> predicateList(vector<Predicate> vec);
    vector<Parameter> parameterList(vector<Parameter> vec);
    void stringList();
    vector<Parameter> idList(vector<Parameter> vec);
    Parameter parameter();
    string expression(string a);
    void op();
};
#endif //SCANNER_PARSER_H
