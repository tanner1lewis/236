//
//  predicate.hpp
//  scanner
//
//  Created by Tanner Lewis on 1/29/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#ifndef predicate_h
#define predicate_h

#include <stdio.h>
#include <string>
#include <vector>
#include "token.h"
#include "parameter.h"


class Predicate {
    
public:
    string name;
    vector<Parameter> parameterList;
    
    Predicate();
    string toString();
    void clear();
};

#endif /* predicate_h */
