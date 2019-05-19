

#ifndef MISSION2_POINTNODE_H
#define MISSION2_POINTNODE_H

#include "Node.h"
#include "Point.h"
#include "Point.h"
#include "PointNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
using namespace std;
using namespace boost::archive;

/*
 this class makes a node of points
 it implements Node with all the functions needed for a pont type node
 */

class PointNode:public Node {
private:
    int size;
    Point p;
    bool isObstacle;
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & size;
        ar & isObstacle;
        ar & p;

    }

public:
    PointNode();

    //query if the node is obstacle
    bool isIsObstacle() const;

    //set flag as obstacle
    void setIsObstacle(bool isObstacle);

    //constructor for given value
    PointNode(Point p, int size);

    //returns the graph size
    int graphSize();

    //prints this node
    ostream& print(ostream&) const;

    //destructor
    ~PointNode();

//returns the point value of PointNode
    Point getPoint();

    bool operator == (const PointNode &pointN)const;
   };
#endif //MISSION2_POINTNODE_H