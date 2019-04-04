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

//    Scheme sch = Scheme();
//    sch.push_back("First");
//    sch.push_back("Second");
//    sch.push_back("Third");
//
//    Relation r = Relation("test", sch);
//
//    Tuple t1 = Tuple();
//    t1.push_back("Tanner");
//    t1.push_back("Lewis");
//    t1.push_back("Provo");
//
//    Tuple t2 = Tuple();
//    t2.push_back("Christian");
//    t2.push_back("lewis");
//    t2.push_back("Provo");
//
//
//    Tuple t3 = Tuple();
//    t3.push_back("Rand");
//    t3.push_back("Lewis");
//    t3.push_back("Rand");
//
//    r.addRow(t3);
//    r.addRow(t1);
//    r.addRow(t2);
//
//    cout << "General Table structure" << endl;
//    r.printOut();
//
//    cout << endl << "Test select" << endl;
//    Relation r2 = r.select1(1, "Lewis");
//    Relation r5 = r.select2(0, 2);
//    r2.printOut();
//    r5.printOut();
//
//    cout << endl << "Test project" << endl;
//    Relation r3 = r.project({"Second", "Third"});
//    r3.printOut();
//
//    cout << endl << "Test rename" << endl;
//    Relation r4 = r.rename("Second", "here");
//    r4.printOut();


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