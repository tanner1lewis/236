//
// Created by Tanner Lewis on 3/29/2019.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include "node.h"

using namespace std;

class Graph {

    map<int, Node> reversedRuleGraph;

    public:
        vector<Node> ruleGraph;
        int postCounter;
        void addNode(Node n);
        void printGraph(int i);
        vector<Node> getGraph();
        vector<int> dfs(int i, vector<int> nodeList, int rev);
        vector<int> dfsForest();
        vector<set<int> > findSCC(vector<int> dfsForestResult);
        // go through the vector of ints returned by dfsForest, start at 
        // the end and call dfs on each node. Each vector that dfs returns
        // is a set of SCC
};


#endif