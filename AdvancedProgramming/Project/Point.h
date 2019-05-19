
#ifndef EX1_POINT_H
#define EX1_POINT_H

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

using namespace std;
using namespace boost::archive;

/*
 this class is the most basic object.
 it holds an x axis and a y axis because it represents a 2 dimensional world.
 */

class Point{
private:
    int x,y;

    friend class boost::serialization::access;
public:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & x;
        ar & y;

    }


    Point(){}

    //constructor for given value
    Point(int x,int y):x(x),y(y){};

    //destructor
    ~Point();

    //operator overloading so we can compare two objects
    bool operator == (const Point &point)const;

    //operator overloading so we can print a point using <<
    friend ostream& operator << (ostream &os, const Point &point);

    //x is private so we have a function to get x
    int getX()const;

    //y is private so we have a function to get y
    int getY()const;
};
#endif //EX1_POINT_H