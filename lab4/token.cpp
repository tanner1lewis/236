//
//  token.cpp
//  scanner
//
//  Created by Tanner Lewis on 1/16/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#include "token.h"

token::token(int num, tokenType t, string v) {
    lineNum = num;
    ttype = t;
    value = v;
}

void token::toString() {
    string token_type;
    switch (ttype) {
        case COMMA:
            token_type = "COMMA";
            break;
        case PERIOD:
            token_type = "PERIOD";
            break;
        case Q_MARK:
            token_type = "Q_MARK";
            break;
        case LEFT_PAREN:
            token_type = "LEFT_PAREN";
            break;
        case RIGHT_PAREN:
            token_type = "RIGHT_PAREN";
            break;
        case COLON:
            token_type = "COLON";
            break;
        case COLON_DASH:
            token_type = "COLON_DASH";
            break;
        case MULTIPLY:
            token_type = "MULTIPLY";
            break;
        case ADD:
            token_type = "ADD";
            break;
        case SCHEMES:
            token_type = "SCHEMES";
            break;
        case FACTS:
            token_type = "FACTS";
            break;
        case RULES:
            token_type = "RULES";
            break;
        case QUERIES:
            token_type = "QUERIES";
            break;
        case ID:
            token_type = "ID";
            break;
        case STRING:
            token_type = "STRING";
            break;
        case COMMENT:
            token_type = "COMMENT";
            break;
        case UNDEFINED:
            token_type = "UNDEFINED";
            break;
        default:
            token_type = "EOF";
    }
    cout << "(" << token_type << ",\"" << value << "\"," << lineNum << ")";
}
