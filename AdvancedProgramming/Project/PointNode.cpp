
#include "PointNode.h"

using namespace std;


/*this class makes a node of points
  it implements Node with all the functions needed for a pont type node
*/

//constructor for a given value
PointNode::PointNode(Point p, int size):p(p),size(size){
}

//returns the graph size
int PointNode::graphSize(){
    return this->size;
}

//destructor
PointNode::~PointNode(){
}

//prints this node
ostream &PointNode::print(ostream &) const {
    cout<<this->p;
}

//returns the point value of PointNode
Point PointNode::getPoint(){
    return this->p;
}

void PointNode::setIsObstacle(bool isObstacle) {
    this->isObstacle = isObstacle;
}

bool PointNode::isIsObstacle() const {
    return this->isObstacle;
}
//operator overloading so we can compare two objects
bool PointNode:: operator == (const PointNode &pointN)const{
   return this->p.operator==(pointN.p);

}

PointNode::PointNode() {

}
