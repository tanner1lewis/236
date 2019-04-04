//
// Created by Tanner Lewis on 2019-03-04.
//

#ifndef RELATION_H
#define RELATION_H

#include <stdio.h>
#include <string>
#include <set>
#include "scheme.h"
#include "tuple.h"

using namespace std;

class Relation {

    string name;
    Scheme schema;
    set<Tuple> rows;
    
    public:
        Relation(string n, Scheme s);
        void addRow(Tuple t);
        void printOut();
        set<Tuple> getRows();
        Scheme getSchema();
        Relation select1(int index, string value);
        Relation select2(int index1, int index2);
        Relation project(vector<string> columns);
        Relation rename(string original, string updated);
};

#endif