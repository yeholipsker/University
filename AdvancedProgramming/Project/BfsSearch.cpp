//
// Created by yehoshua on 24/11/16.
//

#include "BfsSearch.h"
#include <algorithm>

/*
 * class bfsSearch. the class responsible for the algorithm of finding the shortest way while searching
 * the graph in bfs way. it takes abstract node so it will work on any graph that its nodes implementing
 * Node abstract class
 */

using namespace std;
//constructor
BfsSearch::BfsSearch(Node * node) {
    this->root = node;
}

//the function gets node and vector of nodes and returns true if the node is already in the vector
bool BfsSearch::isNodeInVector(vector<Node*> &nodeVector, Node * nodeEnd) {
    for (vector<Node*>::iterator it = nodeVector.begin(); it != nodeVector.end(); ++it) {
        if(*it == nodeEnd) {
            return true;
        }
    }
    return false;
}

//the function assign to a vector all the nodes and there neighbors in the way to the end point
//every node that is added his "father set to the closest father in the way
vector<Node*> BfsSearch::generateNodeInPathVector(Node * nodeEnd) {
    int i = 0;
    vector<Node*> nodeVector;
    vector<Node*> tempNodeVector;
    nodeVector.push_back(this->root);
    while (nodeEnd->getFather() == NULL && nodeVector.size() <= nodeEnd->graphSize()) {
        tempNodeVector = nodeVector[i]->getNeighbors();
        for (int j = 0; j < tempNodeVector.size(); ++j) {
            if (tempNodeVector[j]->getFather() == NULL){
                tempNodeVector[j]->setFather(nodeVector[i]);
                nodeVector.push_back(tempNodeVector[j]);
            }
        }/*
        for (vector<Node*>::iterator it = tempNodeVector.begin(); it != tempNodeVector.end(); ++it) {
            if(!isNodeInVector(nodeVector,*it)) {
                (*it)->setFather(nodeVector[i]);
                nodeVector.push_back(*it);
            }
        }*/
        i++;
    }
    return nodeVector;
}

//the function takes the vector of all the nodes in the way and returns only the ones that creates the
//shortest way (see function fillWayVector
vector<Node*> BfsSearch::findTheWay(Node* nodeEnd){
    vector<Node*> wayVector;
    vector<Node*> tempNodeVector;
    tempNodeVector = this->generateNodeInPathVector(nodeEnd);
    //this->fillWayVector(wayVector, tempNodeVector, nodeEnd);
    if (nodeEnd == this->root) {
        wayVector.push_back(nodeEnd);
        return wayVector;
    }
    do {
        wayVector.push_back(nodeEnd);
        nodeEnd = nodeEnd->getFather();
    } while (nodeEnd != root);
    wayVector.push_back(this->root);
    reverse(wayVector.begin(),wayVector.end());
    return wayVector;
}

//the function gets the vector of all the nodes and in a recursive way it adds to the final vector
//only the nodes that are closest to the start point
void BfsSearch::fillWayVector(vector<Node*> &wayVector, vector<Node *> &tempNodeVector,Node* nodeEnd) {
    /*int index = 0;
    for (int j = 0; j < tempNodeVector.size(); ++j) {
        if (tempNodeVector[j] == nodeEnd) {
            index = j;
        }
    }*/
    wayVector.push_back(nodeEnd);
    if (nodeEnd->getFather() != NULL) {
        this->fillWayVector(wayVector, tempNodeVector, nodeEnd->getFather());
    }
}
