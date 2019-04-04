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

bool Relation::addRow(Tuple t) {
    pair<set<Tuple>::iterator,bool> ret;
    ret = rows.insert(t);
    if (ret.second) {
    }
    return ret.second;
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

vector<Tuple> Relation::newTuples(Relation r) {
    vector<Tuple> newTuples;
    
    set<Tuple> t1 = rows;
    set<Tuple> t2 = r.getRows();
    for (Tuple t : t2) {
        if (find(t1.begin(), t1.end(), t) == t1.end()) {
            newTuples.push_back(t);
        }
    }
    return newTuples;
}

set<Tuple> Relation::getRows() {
    return rows;
}

string Relation::getName() {
    return name;
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
        if (s != "") {
            if (find(schema.begin(), schema.end(), s) != schema.end()) {
                newScheme.push_back(s);
            }
        }
    }

    Relation r = Relation(name, newScheme);

    for (Tuple t : rows) {
        for (unsigned int i = 0; i < newScheme.size(); i++) // Go through all of the attributes in the new Schema
            for (unsigned int j = 0; j < schema.size(); j++) // Go through all of the old attributes
                if (newScheme[i] == schema[j]) // See if any of these attributes are matching
                    newTuple.push_back(t[j]); // Add the tuple index of the matching attributes to the new relation
        
        r.addRow(newTuple);
        newTuple.clear();
    }
    
    return r;
}

Relation Relation::rename(string original, string updated) {
    for (unsigned int i = 0; i < schema.size(); i++) {
        if (schema[i] == original) {
            schema[i] = updated;
            break;
        }
    }

    Relation r = Relation(name, schema);
    r.rows = getRows();
    return r;
}

Relation Relation::r_union(Relation r) {
    for (Tuple t : r.getRows()) {
        addRow(t);
    }
    return r;
}

Relation Relation::join(Relation r1, Relation r2) {
    vector<int> sameCols;
    vector<int> newCols;
    Scheme r1Schema = r1.getSchema();
    Scheme r2Schema = r2.getSchema();
    int added = 0;
    for (unsigned int j = 0; j < r2Schema.size(); j++) {
        for (unsigned int i = 0; i < r1Schema.size(); i++) {
            if (r1Schema[i] == r2Schema[j]) {
                sameCols.push_back(i);
                sameCols.push_back(j);
                added = 1;
            }
        }
        if (!added) {
            newCols.push_back(j);
        }
        added = 0;
    }
    Scheme s = combineSchemes(r1Schema, r2Schema, newCols);
    Relation r = Relation(r1.name, s);
    set<Tuple> set1 = r1.getRows();
    set<Tuple> set2 = r2.getRows();

    for (auto t1 : set1) {
        for (auto t2: set2) {
            if (isJoinable(t1, t2, sameCols)) {
                r.addRow(combineTuples(t1, t2, newCols));
            }
        }
    }

    return r;
}

Scheme Relation::combineSchemes(Scheme s1, Scheme s2, vector<int> indexes) {
    for (int i : indexes) {
        s1.push_back(s2[i]);
    }
    return s1;
}

bool Relation::isJoinable(Tuple t1, Tuple t2, vector<int> indexes) {
    for (unsigned int i = 0; i < indexes.size(); i+=2) {
        if (t1[indexes[i]] != t2[indexes[i+1]]) {
            return false;
        }
    }
    return true;
}

Tuple Relation::combineTuples(Tuple t1, Tuple t2, vector<int> indexes) {
    Tuple newTuple = Tuple();
    for (string s : t1) {
        newTuple.push_back(s);
    }
    for (int i : indexes) {
        newTuple.push_back(t2[i]);
    }
    return newTuple;
}