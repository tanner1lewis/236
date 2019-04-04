//
//  parameter.hpp
//  scanner
//
//  Created by Tanner Lewis on 1/29/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#ifndef parameter_h
#define parameter_h

#include <stdio.h>
#include "token.h"

class Parameter {
    string par;
    bool hasName;
    bool hasExpression;
    bool hasValue;
    
public:
    
    Parameter(string s, bool name, bool expression, bool value);
    string toString();
    bool isString();
    bool isValue();
};

#endif /* parameter_h */
