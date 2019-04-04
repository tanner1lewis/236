//
// Created by Tanner Lewis on 3/29/2019.
//

#ifndef NODE_H
#define NODE_H

#include <set>
#include <string>

using namespace std;

class Node {

    bool visited;
    string nodeName;
    set<int> adjacentNodes;
    set<int> reversedNodes;

    public:
    int postOrder;
    int number;
        Node(){visited = false;};
        void setNumber(int n);
        int getNumber();
        void setName(string s);
        string getName();
        void toggleVisited();
        bool isMarked();
        set<int> getAdjacency();
        void setAdjacency(set<int> nodes);
        void addToAdjacency(int n);
        set<int> getRAdjacency();
        void setRAdjacency(set<int> nodes);
        void addToRAdjacency(int n);
};

#endif