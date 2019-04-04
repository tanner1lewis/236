//
//  datalogprogram.hpp
//  scanner
//
//  Created by Tanner Lewis on 1/29/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#ifndef datalogprogram_h
#define datalogprogram_h

#include <stdio.h>
#include "token.h"
#include "predicate.h"
#include "parameter.h"
#include "rule.h"
#include <set>

class datalog {
    
public:
    vector<Predicate> DLschemes;
    vector<Predicate> DLfacts;
    vector<Predicate> DLqueries;
    vector<Rule> DLrules;
    set<string> domain;
    
    datalog(){};
    void toString();
    void datalogParse();
};

#endif /* datalogprogram_h */
