
#include "Node.h"

/*
  this class is the father type for every class we would like to run in the bfs algorithm.
  the functions in this class are the functions every class that would run bfs would need.
  */

//returns the node that created this node, if there is one.
Node * Node:: getFather(){
    return this->father;
}

//operator overloading so we can print the node by using <<
ostream& operator << (ostream& os, const Node& node) {
    return node.print(os);
}

//gets all the neighbors of the node.
vector<Node*> Node::getNeighbors(){
    return this->neighbors;
}

//adds neighbor to the node
void Node::addNeighbor(Node *node) {
    this->neighbors.push_back(node);
}

//sets the father of this node
void Node::setFather(Node *father) {
    this->father = father;
}

//destructor
Node::~Node() {
}

void Node::clearNeighbors() {
    this->neighbors.clear();
}

