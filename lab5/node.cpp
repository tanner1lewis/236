//
//  node.cpp
//  scanner
//
//  Created by Tanner Lewis on 3/29/19.
//  Copyright © 2019 Tanner Lewis. All rights reserved.
//

#include "node.h"

void Node::setNumber(int n) {
    number = n;
}

int Node::getNumber() {
    return number;
}

void Node::setName(string s) {
    nodeName = s;
}

string Node::getName() {
    return nodeName;
}

void Node::toggleVisited() {
    visited = !visited;
}

bool Node::isMarked() {
    return visited;
}

set<int> Node::getAdjacency() {
    return adjacentNodes;
}

void Node::setAdjacency(set<int> nodes) {
    adjacentNodes = nodes;
}

void Node::addToAdjacency(int n) {
    adjacentNodes.insert(n);
}

set<int> Node::getRAdjacency() {
    return reversedNodes;
}

void Node::setRAdjacency(set<int> nodes) {
    reversedNodes = nodes;
}

void Node::addToRAdjacency(int n) {
    reversedNodes.insert(n);
}