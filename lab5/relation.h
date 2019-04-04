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
        bool addRow(Tuple t);
        void printOut();
        vector<Tuple> newTuples(Relation r);
        set<Tuple> getRows();
        string getName();
        Scheme getSchema();
        Relation select1(int index, string value);
        Relation select2(int index1, int index2);
        Relation project(vector<string> columns);
        Relation rename(string original, string updated);
        Relation r_union(Relation r);
        Relation join(Relation r1, Relation r2);
        Scheme combineSchemes(Scheme s1, Scheme s2, vector<int> indexes);
        bool isJoinable(Tuple t1, Tuple t2, vector<int> indexes);
        Tuple combineTuples(Tuple t1, Tuple t2, vector<int> indexes);
};

#endif