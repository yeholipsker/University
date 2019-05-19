
#ifndef MISSION2_CAB_H
#define MISSION2_CAB_H

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
#include <boost/serialization/export.hpp>
using namespace std;
using namespace boost::archive;


/**
 * class cab. responsible for the moving on the map. this kind of cab
 * moves only one step every time on the map.
 */
class Cab {


protected:
    //members
    enum Manufacturer {HONDA,SUBARO,TESLA,FIAT};
    enum Color {RED,BLUE,GREEN,PINK,WHITE};
    int cabId;
    bool inDrive;
public:
    bool isInDrive() const;

    void setInDrive(bool inDrive);

protected:
    float kilometersPassed;
    Manufacturer manufacturer;
    Color color;
    PointNode * location;
    vector<PointNode *> currentWay;

    friend class boost::serialization::access;
public:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & manufacturer;
        ar & color;
        ar & cabId;
        ar & kilometersPassed;
        ar & location;
        ar & currentWay;
        ar & inDrive;
    }

    const vector<PointNode *> &getCurrentWay() const;

protected:
    double tarrif;


public:
    // default constructor

    Cab();

    //constructor
    Cab(int cabId, char manufacturer, char color, PointNode* location);

    //destructor
    virtual ~Cab();

    //moves the cab along the map
    virtual PointNode * move(vector<PointNode *> v, PointNode * n);

    //gets the cab's id
    int getCabId() const;

    //gets the location of the cab
    PointNode * getLocation() const;

    //sets the location of the cab
    void setLocation(PointNode * location);

    //set the course to the current trip
    void setCurrentWay(const vector<PointNode *> &currentWay);

};


#endif //MISSION2_CAB_H
