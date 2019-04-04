//
//  parser.cpp
//  scanner
//
//  Created by Tanner Lewis on 1/25/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#include "parser.h"

parser::parser(scanner& s) : scanned(s) {
    tokenIndex = 0;
    curr_t = getToken();
}

void parser::parse() {
    datalogProgram();
}

void parser::match(tokenType t) {
    if (curr_t.ttype == t) {
        curr_t = getToken();
    }
    else throw curr_t;
}

token parser::getToken() {
    token t = scanned.tokensV[tokenIndex];
    tokenIndex++;
    return t;
}

void parser::datalogProgram() {
    if (curr_t.ttype == SCHEMES) {
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
        match(FACTS);
        match(COLON);
        factList();
        match(RULES);
        match(COLON);
        ruleList();
        match(QUERIES);
        match(COLON);
        query();
        queryList();
    }
    else throw curr_t;
}

void parser::schemeList() {
    if (curr_t.ttype == ID)
        scheme();
    else if (curr_t.ttype == FACTS) {
    }
    else
        throw curr_t;
    if (curr_t.ttype == ID)
        schemeList();
}

void parser::factList() {
    if (curr_t.ttype == ID)
        fact();
    else if (curr_t.ttype == RULES){}
    else throw curr_t;
    if (curr_t.ttype == ID)
        factList();
}

void parser::ruleList() {
    if (curr_t.ttype == ID)
        rule();
    else if (curr_t.ttype == QUERIES) {}
    else throw curr_t;
    if (curr_t.ttype == ID)
        ruleList();
}

void parser::queryList() {
    if (curr_t.ttype != FILEND) {
        if (curr_t.ttype == ID)
            query();
        else throw curr_t;
        if (curr_t.ttype == ID)
            queryList();
    }
}

void parser::scheme() {
    if (curr_t.ttype == ID) {
        p.name = curr_t.value;
        match(ID);
        match(LEFT_PAREN);
        p.parameterList.push_back(Parameter(curr_t.value, 1,0,0));
        match(ID);
        p.parameterList.push_back(Parameter(curr_t.value, 0,0,1));
        p.parameterList = idList(p.parameterList);
        match(RIGHT_PAREN);
        DL.DLschemes.push_back(p);
        p.clear();
    }
    else throw curr_t;
}

void parser::fact() {
    if (curr_t.ttype == ID) {
        p.name = curr_t.value;
        match(ID);
        match(LEFT_PAREN);
        p.parameterList.push_back(Parameter(curr_t.value, 1,0,0));
        match(STRING);
        p.parameterList.push_back(Parameter(curr_t.value, 0,0,1));
        stringList();
        match(RIGHT_PAREN);
        match(PERIOD);
        DL.DLfacts.push_back(p);
        p.clear();
    }
    else throw curr_t;
}

void parser::rule() {
    Predicate head = headPredicate();
    match(COLON_DASH);
    vector<Predicate> body;
    body.push_back(predicate());
    body = predicateList(body);
    match(PERIOD);
    DL.DLrules.push_back(Rule(head, body));
}

void parser::query() {
    Predicate q = predicate();
    match(Q_MARK);
    DL.DLqueries.push_back(q);
}

Predicate parser::headPredicate() {
    if (curr_t.ttype == ID) {
        Predicate tmp;
        tmp.name = curr_t.value;
        match(ID);
        match(LEFT_PAREN);
        tmp.parameterList.push_back(Parameter(curr_t.value, 1,0,0));
        match(ID);
        tmp.parameterList.push_back(Parameter(curr_t.value, 1,0,0));
        tmp.parameterList = idList(tmp.parameterList);
        match(RIGHT_PAREN);
        return tmp;
    }
    else throw curr_t;
}

Predicate parser::predicate() {
    if (curr_t.ttype == ID) {
        Predicate tmp;
        tmp.name = curr_t.value;
        match(ID);
        match(LEFT_PAREN);
        tmp.parameterList.push_back(parameter());
        tmp.parameterList = parameterList(tmp.parameterList);
        tmp.parameterList.push_back(Parameter(curr_t.value, 0, 1, 0));
        match(RIGHT_PAREN);
        return tmp;
    }
    else throw curr_t;
}

vector<Predicate> parser::predicateList(vector<Predicate> vec) {
    if (curr_t.ttype == COMMA) {        
        match(COMMA);
        vec.push_back(predicate());
        vec = predicateList(vec);
        return vec;
    }
    return vec;
    // else empty string
}

vector<Parameter> parser::parameterList(vector<Parameter> vec) {
    if (curr_t.ttype == COMMA) {
        vec.push_back(Parameter(curr_t.value, 0, 1, 0));
        match(COMMA);
        vec.push_back(parameter());
        vec = parameterList(vec);
        return vec;
    }
    return vec;
    // else empty string
}

void parser::stringList() {
    if (curr_t.ttype == COMMA) {
        match(COMMA);
        p.parameterList.push_back(Parameter(curr_t.value, 1,0,0));
        match(STRING);
        p.parameterList.push_back(Parameter(curr_t.value, 0,0,1));
        stringList();
    }
    // else empty string
}

vector<Parameter> parser::idList(vector<Parameter> vec) {
    if (curr_t.ttype == COMMA) {
        match(COMMA);
        vec.push_back(Parameter(curr_t.value, 1,0,0));
        match(ID);
        vec.push_back(Parameter(curr_t.value, 0,0,1));
        vec = idList(vec);
    }
    return vec;
    // else Empty string
}

Parameter parser::parameter() {
    if (curr_t.ttype == STRING) {
        Parameter a = Parameter(curr_t.value, 1, 0, 0);
        match(STRING);
        return a;
    }
    else if (curr_t.ttype == ID) {
        Parameter a = Parameter(curr_t.value, 0, 0, 1);
        match(ID);
        return a;
    }
    else {
        string a;
        a = expression(a);
        return Parameter(a, 0, 1, 0);
    }
}

string parser::expression(string a) {
    if (curr_t.ttype == LEFT_PAREN) {
        match(LEFT_PAREN);
        a += parameter().toString();
        //a += curr_t.value;
        //parameter();
        a += curr_t.value;
        op();
        //a += curr_t.value;
        a += parameter().toString();
        match(RIGHT_PAREN);
    }
    else throw curr_t;
    return a;
}

void parser::op() {
    if (curr_t.ttype == ADD) match(ADD);
    else if (curr_t.ttype == MULTIPLY) match(MULTIPLY);
    else throw curr_t;
}

