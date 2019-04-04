//
//  rule.cpp
//  scanner
//
//  Created by Tanner Lewis on 1/29/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#include "rule.h"

Rule::Rule(Predicate h, vector<Predicate> b) {
    headP = h;
    bodyP = b;
}

string Rule::toString() {
    string s =headP.toString() + " :- ";
    for (unsigned int i = 0; i < bodyP.size(); i++) {
        s += bodyP[i].toString();
        if (i != bodyP.size()-1) {
            s+=",";
        }
    }
    return s;
}

//void rule::clear() {
//    headP.clear();
//    bodyP.clear();
//}
