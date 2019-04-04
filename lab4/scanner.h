//
//  scanner.h
//  scanner
//
//  Created by Tanner Lewis on 1/14/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#ifndef scanner_h
#define scanner_h

#include <vector>
#include <fstream>
#include <sstream>

#include "token.h"

using namespace std;

class scanner {
    int lineNum;

public:
    vector<token> tokensV;
    stringstream s;

    scanner();

    void scanToken();
    void printVector();
    void createToken(int num, tokenType t, string i);
};

#endif /* scanner_h */
