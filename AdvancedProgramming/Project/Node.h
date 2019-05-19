
#ifndef EX1_NODE_H
#define EX1_NODE_H
#include <iostream>
#include <vector>
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
  this class is the father type for every class we would like to run in the bfs algorithm.
  the functions in this class are the functions every class that would run bfs would need.
  */


class Node {
private:

    //prints this node
    virtual ostream& print(ostream&) const = 0;
protected:
    Node * father;
    vector<Node*> neighbors;
    friend class boost::serialization::access;
public:

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & neighbors;
        ar & father;
    }

    Node(){}

    //adds neighbor to the node
    void addNeighbor(Node* node);

    //clears the neighbors vector
    void clearNeighbors();

    //returns the node that created this node, if there is one.
    Node * getFather();

    //sets the father of this node
    void setFather(Node * father);

    //returns the size of the graph the bfs is running on.
    virtual int graphSize() = 0;

    //gets all the neighbors of the node.
    vector <Node*> getNeighbors();

    //operator overloading so we can print the node by using <<
    friend ostream& operator << (ostream& os, const Node& node);

    //destructor
    virtual ~Node();
    //operator overloading so we can compare two objects
    bool operator == (const Node &node)const;
};


#endif //EX1_NODE_H