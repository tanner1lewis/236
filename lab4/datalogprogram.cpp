//
//  datalogprogram.cpp
//  scanner
//
//  Created by Tanner Lewis on 1/29/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#include "datalogprogram.h"

// void print(const string& item)
// {
//     cout << "  " << item << endl;
// }

void datalog::toString() {
    cout << "Schemes(" << DLschemes.size() << "):" << endl;
    //if (DLschemes.size() > 0) cout << "  " << DLschemes[0].toString();
    for (unsigned int i = 0; i < DLschemes.size(); i++) {
        cout << "  " << DLschemes[i].toString() << endl;
    }
    cout << "Facts(" << DLfacts.size() << "):" << endl;
    //if (DLfacts.size() > 0) cout << "\n  " << DLfacts[0].toString();
    for (unsigned int i = 0; i < DLfacts.size(); i++) {
        cout << "  " << DLfacts[i].toString() << "." << endl;
        for (unsigned int j = 0; j < DLfacts[i].parameterList.size(); j++) {
            if (DLfacts[i].parameterList[j].isString()) {
                domain.insert(DLfacts[i].parameterList[j].toString());
            }
        }
    }
    cout << "Rules(" << DLrules.size() << "):" << endl;
    //if (DLrules.size() > 0) cout << "\n  " << DLrules[0].toString();
    for (unsigned int i = 0; i < DLrules.size(); i++) {
        cout << "  " << DLrules[i].toString() << "." << endl;
    }
    cout << "Queries(" << DLqueries.size() << "):" << endl;
    //if (DLqueries.size() > 0) cout << "\n  " << DLqueries[0].toString();
    for (unsigned int i = 0; i < DLqueries.size(); i++) {
        cout << "  " << DLqueries[i].toString() << "?" << endl;
    }
    cout << "Domain(" << domain.size() << "):" << endl;
    for (string s: domain) {
        cout << "  " << s << endl;
    }
    //for_each(domain.begin(), domain.end(), &print);
}

