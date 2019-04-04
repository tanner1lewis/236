//
// Created by Tanner Lewis on 2019-03-04.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "datalogprogram.h"
#include "database.h"

class Interpreter {
    datalog& data;
    Database db;
    
    public:
        Interpreter(datalog& dl);
        void fillDatabase();
        void addRelation(Predicate p);
        void addTuple(Predicate p);
        void printDatabase();
        Relation getRelation(string s);
        Relation query(Predicate p);
        void allQueries();
};

#endif