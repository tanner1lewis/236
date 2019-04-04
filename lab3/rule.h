//
//  rule.hpp
//  scanner
//
//  Created by Tanner Lewis on 1/29/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#ifndef rule_h
#define rule_h

#include <stdio.h>
#include "predicate.h"

class Rule {
public:
    Predicate headP;
    vector<Predicate> bodyP;

    Rule(Predicate h, vector<Predicate> b);
    string toString();
};

#endif /* rule_h */
