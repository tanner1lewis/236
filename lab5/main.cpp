//
//  main.cpp
//  scanner
//
//  Created by Tanner Lewis on 1/14/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
/*
    Scheme sch = Scheme();
    sch.push_back("First");
    sch.push_back("Second");
    sch.push_back("Third");

    Relation r = Relation("test", sch);

    Tuple t1 = Tuple();
    t1.push_back("Tanner");
    t1.push_back("Lewis");
    t1.push_back("Provo");

    Tuple t2 = Tuple();
    t2.push_back("Christian");
    t2.push_back("lewis");
    t2.push_back("Provo");


    Tuple t3 = Tuple();
    t3.push_back("Rand");
    t3.push_back("Lewis");
    t3.push_back("Rand");

    r.addRow(t3);
    r.addRow(t1);
    r.addRow(t2);

    cout << "General Table structure" << endl;
    r.printOut();

    cout << endl << "Test select" << endl;
    Relation r2 = r.select1(1, "Lewis");
    Relation r5 = r.select2(0, 2);
    r2.printOut();
    r5.printOut();

    cout << endl << "Test project" << endl;
    Relation r3 = r.project({"Second", "Third"});
    r3.printOut();

    cout << endl << "Test rename" << endl;
    Relation r4 = r.rename("Second", "here");
    r4.printOut();

    Scheme sch = Scheme();
    sch.push_back("cat");
    sch.push_back("dog");
    sch.push_back("fish");


    Scheme sch1 = Scheme();
    sch1.push_back("cat");
    sch1.push_back("fish");
    sch1.push_back("bird");
    sch1.push_back("bunny");

    Relation r = Relation("alpha", sch);
    Relation r2 = Relation("beta", sch1);

    Tuple t1 = Tuple();
    t1.push_back("1");
    t1.push_back("2");
    t1.push_back("5");

    Tuple t2 = Tuple();
    t2.push_back("1");
    t2.push_back("4");
    t2.push_back("1");

    Tuple t3 = Tuple();
    t3.push_back("2");
    t3.push_back("3");
    t3.push_back("2");

    Tuple t4 = Tuple();
    t4.push_back("3");
    t4.push_back("3");
    t4.push_back("2");

    Tuple t9 = Tuple();
    t9.push_back("6");
    t9.push_back("7");
    t9.push_back("4");

    r.addRow(t1);
    r.addRow(t2);
    r.addRow(t3);
    r.addRow(t4);
    r.addRow(t9);

    Tuple t5 = Tuple();
    t5.push_back("3");
    t5.push_back("4");
    t5.push_back("2");
    t5.push_back("4");

    Tuple t6 = Tuple();
    t6.push_back("6");
    t6.push_back("4");
    t6.push_back("9");
    t6.push_back("2");

    Tuple t10 = Tuple();
    t10.push_back("4");
    t10.push_back("3");
    t10.push_back("2");
    t10.push_back("7");

    Tuple t7 = Tuple();
    t7.push_back("1");
    t7.push_back("5");
    t7.push_back("2");
    t7.push_back("4");

    Tuple t8 = Tuple();
    t8.push_back("1");
    t8.push_back("5");
    t8.push_back("8");
    t8.push_back("3");

    r2.addRow(t5);
    r2.addRow(t6);
    r2.addRow(t7);
    r2.addRow(t8);
    r2.addRow(t10);

    r = r.join(r, r2);
    cout << endl << "New relation is " << endl;
    r.printOut();

    Scheme sch = Scheme();
    sch.push_back("x");
    sch.push_back("a");

    Scheme sch1 = Scheme();
    sch1.push_back("y");
    sch1.push_back("b");

    Scheme sch3 = Scheme();
    sch3.push_back("z");
    sch3.push_back("c");

    Relation r = Relation("alpha", sch);
    Relation r2 = Relation("beta", sch1);
    Relation r3 = Relation("gamma", sch3);

    Tuple t1 = Tuple();
    t1.push_back("eggs");
    t1.push_back("bacon");

    Tuple t2 = Tuple();
    t2.push_back("oatmeal");
    t2.push_back("apple");
    r.addRow(t1);
    r.addRow(t2);

    Tuple t3 = Tuple();
    t3.push_back("sandwich");
    t3.push_back("banana");

    Tuple t4 = Tuple();
    t4.push_back("pasta");
    t4.push_back("soup");
    r2.addRow(t3);
    r2.addRow(t4);

    Tuple t5 = Tuple();
    t5.push_back("pasta");
    t5.push_back("broccoli");
    r3.addRow(t5);

    r = r.join(r, r2);
    r = r.join(r, r3);
    r.printOut();
    
    
    Node a = Node();
    a.setNumber(0);
    a.addToAdjacency(1);
    a.addToAdjacency(2);

    Node b = Node();
    b.setNumber(1);
    b.addToAdjacency(0);
    
    Node c = Node();
    c.setNumber(2);
    c.addToAdjacency(1);
    c.addToAdjacency(2);
    
    Node d = Node();
    d.setNumber(3);
    
    Node e = Node();
    e.setNumber(4);
    e.addToAdjacency(3);
    e.addToAdjacency(4);
    
    Graph firstGraph = Graph();
    firstGraph.addNode(a);
    firstGraph.addNode(b);
    firstGraph.addNode(c);
    firstGraph.addNode(d);
    firstGraph.addNode(e);

    cout << "Forward graph is " << endl;
    firstGraph.printGraph(1);
    cout << "reverse graph is " << endl;
    firstGraph.printGraph(0);

    vector<int> adfs;
    vector<int> adfs2;
    adfs = firstGraph.dfs(0, adfs);
    cout << "DFS graph of Node 0 is " << endl;
    for (int i : adfs) {
        cout << i << endl;
    }

    vector<int> forest = firstGraph.dfsForest();
    cout << "DFS forest of is " << endl;
    for (int i : forest) {
        cout << i << endl;
    }

*/
    string str;
    char tmp;
    ifstream input_file;
    input_file.open(argv[1]);
    //input_file.open("/Users/tannerlewis/Documents/CS/scanner/scanner/parser/in62.txt");
    if (input_file.is_open()) {
        while (input_file.get(tmp)){
            str.push_back(tmp);
        }
    //scanner s(str);
    scanner s;
    s.s << str;
    s.scanToken();
    //s.printVector();

    input_file.close();

    parser p(s);

    try {
        p.parse();
        Interpreter i = Interpreter(p.DL);
        i.fillDatabase();
        i.allRules();
        i.allQueries();
        //cout << "Success!" << endl;

        } catch (token t) {
            cout << "Failure!" << endl;
            cout << "  ";
            t.toString();
            cout << "\n";
        }
    }
    else {
        cout << "Unable to open file" << endl;
    }
    return 0;
}