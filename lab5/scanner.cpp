//
//  token.cpp
//  scanner
//
//  Created by Tanner Lewis on 1/14/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#include "scanner.h"
#include "token.h"

scanner::scanner() {
    lineNum = 1;
}

void scanner::printVector() {
    for (auto &i : tokensV) {
        i.toString();
    }
    cout << "Total Tokens = " << tokensV.size();
}

void scanner::createToken(int num, tokenType t, string i) {
    token a(num, t, i);
    tokensV.insert(tokensV.end(), a);
}

void scanner::scanToken() {
    while (true) {
        char input = static_cast<char>(s.get());
        if (input <= 0) {
            string empty = "";
            createToken(lineNum, FILEND, empty);
            break;
        };
        if (input == '\n')  lineNum++;
        else if (isspace(input) || input == '\t') continue;
        else {
            string alta;
            switch (tolower(input)) {
                case ',': {
                    alta.push_back(input);
                    createToken(lineNum, COMMA, alta);
                    break;
                }
                case '.': {
                    alta.push_back(input);
                    createToken(lineNum, PERIOD, alta);
                    break;
                }
                case '?': {
                    alta.push_back(input);
                    createToken(lineNum, Q_MARK, alta);
                    break;
                }
                case '(': {
                    alta.push_back(input);
                    createToken(lineNum, LEFT_PAREN, alta);
                    break;
                }
                case ')': {
                    alta.push_back(input);
                    createToken(lineNum, RIGHT_PAREN, alta);
                    break;
                }
                case ':': {
                    alta.push_back(input);
                    if (s.peek() == '-') {
                        alta.push_back(s.get());
                        createToken(lineNum, COLON_DASH, alta);
                    }
                    else {
                        createToken(lineNum, COLON, alta);
                    }
                    break;
                }
                case '*': {
                    alta.push_back(input);
                    createToken(lineNum, MULTIPLY, alta);
                    break;
                }
                case '+': {
                    alta.push_back(input);
                    createToken(lineNum, ADD, alta);
                    break;
                }
                case '\'': {
                    int i = 0;
                    int temp_linenum = lineNum;
                    alta.push_back(input);
                    input = static_cast<char>(s.get());
                    alta.insert(alta.end(), input);
                    while (true) {
                        if (input == '\n') lineNum++;
                        if ((input =='\'') && (s.peek() != '\'')) {
                            break;
                        }
                        else if ((input =='\'') && (s.peek() == '\'')) {
                            input = s.get();
                            alta.insert(alta.end(), input);
                            input = s.get();
                            alta.insert(alta.end(), input);
                        }
                        else {
                            input = s.get();
                            if (input == EOF) {
                                createToken(temp_linenum, UNDEFINED, alta);
                                i = 1;
                                break;
                            }
                            else alta.insert(alta.end(), input);
                        }

                    }
                    if (!i) createToken(temp_linenum, STRING, alta);
                    break;
                }
                case '#': {
                    int i = 0;
                    alta.push_back(input);
                    //int temp_lineNum = lineNum;
                    if (s.peek() == '|') { // Start of a multi-line comment
                        input = s.get();
                        alta.insert(alta.end(), input);
                        while (true) {
                            input = s.get();
                            if (input == '|' && s.peek() == '#') {
                                break;
                            }
                            if (input == EOF) {
                                i = 1;
                                break;
                            }
                            alta.insert(alta.end(), input);
                            if (input == '\n') lineNum++;
                        }
                        if (input == EOF) {
                            //createToken(temp_lineNum, UNDEFINED, alta);
                            i = 1;
                        }
                        else {
                            alta.insert(alta.end(), input);
                            input = s.get();
                            if (input == EOF) {
                                //createToken(temp_lineNum, UNDEFINED, alta);
                                i = 1;
                            }
                            else {
                                alta.insert(alta.end(), input);
                            }
                        }
                    }
                    else {
                        while (s.peek() != '\n') {
                            input = s.get();
                            alta.insert(alta.end(), input);
                        }
                    }
                    if (i) 
                        ;
                    //if (!i) createToken(temp_lineNum, COMMENT, alta);
                    break;
                }
                default:
                    alta.push_back(input);
                    if (isalpha(input)) {
                        while (!isspace(s.peek()) && isalnum(s.peek())) {
                            if (s.peek() == EOF) {
                                createToken(lineNum, UNDEFINED, alta);
                                break;
                            }
                            input = s.get();
                            alta.insert(alta.end(), input);
                        }
                        if (alta == "Schemes") {
                            createToken(lineNum, SCHEMES, alta);
                        }
                        else if (alta == "Rules") {
                            createToken(lineNum, RULES, alta);
                        }
                        else if (alta == "Facts") {
                            createToken(lineNum, FACTS, alta);
                        }
                        else if (alta == "Queries") {
                            createToken(lineNum, QUERIES, alta);
                        }
                        else createToken(lineNum, ID, alta);
                    }
                    else createToken(lineNum, UNDEFINED, alta);
                    break;
            }
        }

    }
}

