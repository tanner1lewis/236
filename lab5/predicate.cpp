//
//  predicate.cpp
//  scanner
//
//  Created by Tanner Lewis on 1/29/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#include "predicate.h"

Predicate::Predicate() {}

string Predicate::toString() {
    string ret = name + "(";
    for (unsigned int i = 0; i < parameterList.size(); i++) {
        ret += parameterList[i].toString();
    }
    return ret;
}

void Predicate::clear() {
    name = "";
    parameterList.clear();
}
