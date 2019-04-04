//
//  relation.cpp
//  scanner
//
//  Created by Tanner Lewis on 1/25/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include "relation.h"

Relation::Relation(string n, Scheme s) {
    name = n;
    schema = s;
}

void Relation::addRow(Tuple t) {
    rows.insert(t);
}

void Relation::printOut() {
    for (Tuple t : rows) {
         unsigned int i;
         cout << endl << "  ";
         if (t.size() > 1) {
             for (i = 0; i < t.size()-1; i++) {
                 cout << schema[i] << "=" << t[i] << ", ";
             }
             cout << schema[i] << "=" << t[i];
         }
         else {
             cout << schema[0] << "=" << t[0] << "";
         }
     }
}

set<Tuple> Relation::getRows() {
    return rows;
}

Scheme Relation::getSchema() {
    return schema;
}

Relation Relation::select1(int index, string value) {
    Relation r = Relation(name, schema);
    for (Tuple t : rows)
        if (t[index] == value)
            r.addRow(t);
    return r;
}

Relation Relation::select2(int index1, int index2) {
    Relation r = Relation(name, schema);
    for (Tuple t : rows)
        if (t[index1] == t[index2])
            r.addRow(t);
    return r;
}

Relation Relation::project(vector<string> columns) {
    Scheme newScheme = Scheme();
    Tuple newTuple = Tuple();
    for (string s : columns) {
        if (find(schema.begin(), schema.end(), s) != schema.end()) {
            newScheme.push_back(s);
        }
    }

    Relation r = Relation(name, newScheme);

    for (Tuple t : rows) {
        for (unsigned int i = 0; i < schema.size(); i++) {
            for (string s : columns) {
                if (s == schema[i]) {
                    newTuple.push_back(t[i]);
                }
            }
            //if (columns.find(schema[i]) !+ columns.end()) {
            //if (find(columns.begin(), columns.end(), schema[i]) != columns.end()) {

            //}
        }
        r.addRow(newTuple);
        newTuple.clear();
    }
    return r;
}

Relation Relation::rename(string original, string updated) {
    for (unsigned int i = 0; i < schema.size(); i++) {
        if (schema[i] == original) {
            schema[i] = updated;
        }
    }

    Relation r = Relation(name, schema);
    r.rows = getRows();
    return r;
}
