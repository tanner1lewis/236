//
//  parameter.cpp
//  scanner
//
//  Created by Tanner Lewis on 1/29/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#include "parameter.h"

Parameter::Parameter(string s, bool name, bool expression, bool value) {
    par = s;
    hasName = name;
    hasExpression = expression;
    hasValue = value;
}

string Parameter::toString() {
    if (hasName || hasValue) {
        return par;
    }
    else {
        //string s = "(" + par + ")";
        return par;
    }
}

bool Parameter::isString() {
    return hasName;
}

bool Parameter::isValue() {
    return hasValue;
}
