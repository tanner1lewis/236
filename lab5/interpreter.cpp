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
    for (unsigned int i = 0; i < p.parameterList.size(); i++) { // Select
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
    for (auto e : variables) { // Rename
        r = r.rename(s_original[e.second], e.first);
    }
    
    map<int, string> reversed;
    for (auto i = variables.begin(); i != variables.end(); ++i)
        reversed[i->second] = i->first;
    
    if (!reversed.empty()) { // Project
        vector<string> cols(reversed.size());
        for (auto e : reversed) {
            cols.push_back(e.second);
        }
        r = r.project(cols);
    }
    
    return r;
}

void Interpreter::allQueries() {
    cout << "Query Evaluation" << endl;
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

Relation Interpreter::rule(Rule r) {
    vector<Relation> relations;
    for (Predicate p : r.bodyP) {
        relations.push_back(query(p));
    }
    Relation R = relations[0];
    
    if (relations.size() > 1) {
        for (unsigned int i = 1; i < relations.size(); i++) {
            R = R.join(R, relations[i]);
        }
    }
    return R;
}

void Interpreter::allRules() {
    int iterations = 0;
    int changed = 0;

    Graph myGraph = Graph();
    vector<Rule> rules = data.DLrules;
    for (unsigned int i = 0; i < rules.size(); i++) {
        Node n = Node();
        n.setNumber(i);
        n.setName(rules[i].headP.name);
        myGraph.addNode(n);
    }
    
    for (unsigned int i = 0; i < rules.size(); i++) {
        for (Predicate p : rules[i].bodyP) {
            for (unsigned int j = 0; j < rules.size(); j++) {
                if (p.name == rules[j].headP.name) {
                    myGraph.ruleGraph[i].addToAdjacency(j);
                    myGraph.ruleGraph[j].addToRAdjacency(i);
                }
            }
        }
    }
    
    myGraph.printGraph(1); // Print out the graph with the adjacency list
    //myGraph.printGraph(0); // Print out reverse dependency graph
    cout << endl << "Rule Evaluation" << endl;

    myGraph.postCounter = 1;
    vector<int> forest = myGraph.dfsForest();

    vector<set<int> > sccs = myGraph.findSCC(forest);
    //cout << "SCC size is "<< sccs.size() << endl;
    for (set<int> i : sccs) { // Iterate through all of our SCCs
        int sccSize = i.size(); // Find the size. If it is 0 or 1 we only want to run the fixed-point loop once
        int depends = 0; // This will tell us if the rule depends on itself and if we should run the algorithm multiple times
        
        set<int>::iterator it = i.begin();
        cout << "SCC: R" << *it;
        it++;
        while (it != i.end()) {
            cout << ",R" <<  *it;
            it++;
        }
        iterations = 0;
        do {
            changed = 0;
            Relation R = Relation("Holder", Scheme());
            for (int j : i) {
                Rule r = data.DLrules[j];
                R = rule(r);
                
                Predicate head = r.headP;
                vector<Parameter> paramList = head.parameterList;
                vector<string> projectCols;

                for (Predicate p : r.bodyP) {
                    if (head.name == p.name) {
                        depends = 1;
                    }
                }

                for (unsigned int i = 0; i < paramList.size(); i++) {
                    if (paramList[i].isString() && paramList[i].toString() != ",") {
                        projectCols.push_back(paramList[i].toString());
                    }
                }
                
                R = R.project(projectCols);
                
                for (Predicate p : data.DLschemes) {
                    if (p.name == head.name) {
                        for (unsigned int j = 0; j < p.parameterList.size(); j++) {
                            if (p.parameterList[j].isString()) {
                                R = R.rename(head.parameterList[j].toString(), p.parameterList[j].toString());
                            }
                        }
                    }
                }
                Relation original = getRelation(head.name);
                R = original.r_union(R);
                
                Relation old = db.at(head.name);
                
                set<Tuple> oldRows = old.getRows();
                Relation final = Relation(R.getName(), R.getSchema());
                for (Tuple t : R.getRows()) {
                    if (old.addRow(t)) {
                        final.addRow(t);
        
                    }
                }
                set<Tuple> newT = old.getRows();
                
                vector<Tuple> newRows = old.newTuples(R);
                if (oldRows.size() != newT.size()) {changed = 1;}
                

                cout << endl << r.toString() << ".";
                final.printOut();
                db.at(head.name) = old;
                
            }
            
            iterations++;
            it = i.begin();
            if ((sccSize < 2) && !depends) changed = 0;
        }
        while (changed);
        it = i.begin();
        cout << endl << iterations << " passes: R" << *it;
        it++;
        while (it != i.end()) {
            cout << ",R" << *it;
            it++;
        }
        cout << endl;
    }
    cout << endl;
    //cout << endl << "Schemes populated after "<< iterations << " passes through the Rules." << endl << endl;
}