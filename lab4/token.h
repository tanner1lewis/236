//
//  token.h
//  scanner
//
//  Created by Tanner Lewis on 1/16/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#ifndef token_h
#define token_h

#include <string>
#include <map>
#include <iostream>

using namespace std;

enum tokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH,
    MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, FILEND};

class token {

//     map<tokenType, string> tokenMap = {
//         {COMMA, "COMMA"},{PERIOD, "PERIOD"},{Q_MARK, "Q_MARK"},{LEFT_PAREN, "LEFT_PAREN"},
//         {RIGHT_PAREN, "RIGHT_PAREN"},{COLON, "COLON"},{COLON_DASH, "COLON_DASH"},
//         {MULTIPLY, "MULTIPLY"},{ADD, "ADD"},{SCHEMES, "SCHEMES"},{FACTS, "FACTS"},{RULES, "RULES"},
//         {QUERIES, "QUERIES"},{ID, "ID"},{STRING, "STRING"},{COMMENT, "COMMENT"},{UNDEFINED, "UNDEFINED"},
//         {FILEND, "EOF"}
//     };

public:
    int lineNum;
    tokenType ttype;
    string value;
    token(){};
    token(int num, tokenType t, string v);
    ~token() = default;;
    void toString();
};

#endif /* token_h */
