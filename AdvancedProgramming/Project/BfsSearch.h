//
// Created by yehoshua on 24/11/16.
//

#ifndef MISSION2_BFSSEARCH_H
#define MISSION2_BFSSEARCH_H

#include <vector>
#include "Node.h"

using namespace std;

/*
 * class bfsSearch. the class responsible for the algorithm of finding the shortest way while searching
 * the graph in bfs way. it takes abstract node so it will work on any graph that its nodes implementing
 * Node abstract class
 */
class BfsSearch {
private:
    //members
    Node * root;
    //the function assign to a vector all the nodes and there neighbors in the way to the end point
    //every node that is added his "father set to the closest father in the way
    vector<Node *> generateNodeInPathVector(Node * nodeEnd);
    //the function gets node and vector of nodes and returns true if the node is already in the vector
    bool isNodeInVector(vector<Node*> &nodeVector, Node * nodeEnd);
    //the function gets the vector of all the nodes and in a recursive way it adds to the final vector
    //only the nodes that are closest to the start point
    void fillWayVector(vector<Node *> &wayVector, vector<Node *> &tempV, Node* nodeEnd);

public:
    //constructor
    BfsSearch(Node * node);
    //the function takes the vector of all the nodes in the way and returns only the ones that creates the
    //shortest way (see function fillWayVector
    vector<Node *> findTheWay(Node *nodeEnd);
};


#endif //MISSION2_BFSSEARCH_H
