//
//  graph.cpp
//  scanner
//
//  Created by Tanner Lewis on 3/29/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#include "graph.h"
#include <iostream>

void Graph::addNode(Node n) {
    ruleGraph.push_back(n);
}

/* Print the current graph with its adjacency list
 * If the int that is passed in is anything but 0, it will print out
 * the normal adjacency list. If the int is 0 then it will print out the 
 * reversed adjacency list
 */
void Graph::printGraph(int i) {
    cout << "Dependency Graph" << endl;
    for (Node n : ruleGraph) {
        cout << "R" << n.number << ":";
        set<int> tmp;
        if (i) tmp = n.getAdjacency();
        else tmp = n.getRAdjacency();
        set<int>::iterator it = tmp.begin();
        if (it != tmp.end()) {
            cout << "R" << *it;
            it++;
            while (it != tmp.end()) {
                cout << ",R" << *it;
                it++;
            }
        }
        cout << endl;
    }
}

vector<Node> Graph::getGraph() {
    return ruleGraph;
}

vector<int> Graph::dfs(int nodeIndex, vector<int> nodeList, int rev) {
    Node n = ruleGraph[nodeIndex];
    if (!n.isMarked()) {
      ruleGraph[nodeIndex].toggleVisited();
    } 
    set<int> adjacentNodes;
    if (rev) adjacentNodes = n.getRAdjacency();
    else adjacentNodes = n.getAdjacency();
    
    for (int i : adjacentNodes) {
        Node nod = ruleGraph[i];
        if (!nod.isMarked()) {
            nodeList = dfs(i, nodeList, rev);
        }
    }
    nodeList.push_back(nodeIndex);  
    ruleGraph[nodeIndex].postOrder = postCounter;
    postCounter++;
    return nodeList;
}

vector<int> Graph::dfsForest() {
    for (unsigned int i = 0; i < ruleGraph.size(); i++) {
        if (ruleGraph[i].isMarked()) ruleGraph[i].toggleVisited();
    }

    vector<int> ret;
    for (Node n : ruleGraph) {
        if (!n.isMarked()) {
            ret = dfs(n.number, ret, 1);
        }
    }
    
    return ret;
    // for (auto e : ruleGraph) {
    //     if (e.second.isMarked()) e.second.toggleVisited();
    // }
    // vector<int> forest;
    // for (auto e : ruleGraph) {
    //     if (!e.second.isMarked()) {
    //         vector<int> ret = dfs(e.second);
    //         forest.insert(forest.end(), ret.begin(), ret.end());
    //     }
    // }
    // return forest;
}

vector<set<int> > Graph::findSCC(vector<int> dfsForestResult) {
    vector<set<int> > SCCsets;
    
    // for (int i : dfsForestResult) {
    //     cout << i << ",";
    // }
    for (unsigned int i = 0; i < ruleGraph.size(); i++) {
        if (ruleGraph[i].isMarked()) ruleGraph[i].toggleVisited();
    }

    for (int j : dfsForestResult) {
        vector<int> scc;
        if (!ruleGraph[j].isMarked()) {
            scc = dfs(j, scc, 1);
            set<int> tmp;
            for (int i : scc) {
                tmp.insert(i);
            }
            SCCsets.insert(SCCsets.begin(), tmp);
        }
    }
    return SCCsets;
}
