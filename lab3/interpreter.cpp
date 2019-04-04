//
//  interpreter.cpp
//  scanner
//
//  Created by Tanner Lewis on 1/25/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#include "interpreter.h"


Interpreter::Interpreter(datalog& dl) : data(dl){
    db = Database();
}

void Interpreter::fillDatabase() {
    for (Predicate p : data.DLschemes) {
        addRelation(p);
    }
    for (Predicate p : data.DLfacts) {
        addTuple(p);
    }
}

void Interpreter::addRelation(Predicate p) {
    Scheme s = Scheme();
    for (Parameter param : p.parameterList){
        if (param.isString())
            s.push_back(param.toString());
    }
    Relation r = Relation(p.name, s);
    db.insert(pair<string, Relation>(p.name, r));
}

void Interpreter::addTuple(Predicate p) {
    Tuple t = Tuple();
    for (Parameter param : p.parameterList)
        if (param.isString())
            t.push_back(param.toString());

    db.at(p.name).addRow(t);
}

void Interpreter::printDatabase() {
    for (auto e : db) {
        cout << "Table name is: " << e.first << endl;
        e.second.printOut();
    }
}

Relation Interpreter::getRelation(string s) {
    return db.at(s);
}

Relation Interpreter::query(Predicate p) {
    Relation r = getRelation(p.name);
    Scheme s_original = r.getSchema();
    map<string, int> variables;
    unsigned int j = 0;
    for (unsigned int i = 0; i < p.parameterList.size(); i++) {
        if (p.parameterList[i].isString()) {
            r = r.select1(j, p.parameterList[i].toString());
            j++;
        }
        else if (p.parameterList[i].isValue()) {
            if (variables.find(p.parameterList[i].toString()) != variables.end()) {
                r = r.select2(variables[p.parameterList[i].toString()], j);
            }
            else {

                variables[p.parameterList[i].toString()] = j;
            }
            j++;
        }
    }

    for (auto e : variables) {
        r = r.rename(s_original[e.second], e.first);
    }
    map<int, string> reversed;
    for (auto i = variables.begin(); i != variables.end(); ++i)
        reversed[i->second] = i->first;
    if (!reversed.empty()) {
        vector<string> cols(reversed.size());
        for (auto e : reversed) {
            cols.push_back(e.second);
        }
        r = r.project(cols);
    }
    return r;
}

void Interpreter::allQueries() {
    for (unsigned int i = 0; i < data.DLqueries.size(); i++) {
        Predicate p = data.DLqueries[i];
        Relation r = query(p);
        set<Tuple> rows = r.getRows();
        if (i) {
            cout << endl;
        }
        if (rows.size() > 0) {
            cout << p.toString() << "? Yes(" << rows.size() << ")";
            int k = 0;
            for (Parameter par : p.parameterList) {
                if (par.isValue()) {
                    k = 1;
                }
            }
            if (k)
                r.printOut();
        }
        else {
            cout << p.toString() << "? No";
        }
    }
}