/*
 * this class is responsible for all what a driver member needs.
 * it has all of his data,
 */
#include "Driver.h"
#include <boost/lexical_cast.hpp>

//constructor
// gets char ang assigns an enum that is equivalent to the caller of the ctor's choice.
Driver::Driver(int id, int age,char maritialStatus, Cab * cab, int experience, PointNode* location) :
        id(id), age(age), cab(cab), experience(experience),location(location) {
    switch (maritialStatus){

        case 'S': status=SINGLE;
            break;
        case 'M':status= MARRIED;
            break;
        case 'D':status=DIVORCED;
            break;
        case 'W':status=WIDOWED;

    }

}



//gets the driver's id

int Driver::getId() {
    return this->id;
}

//gets the location of the driver
PointNode * Driver::getLocation() const {
    return location;
}

//sets the location of the driver
void Driver::setLocation(PointNode *location) {
    Driver::location = location;
}

//sets the way
void Driver::setCurrentWay(const vector<PointNode *> &currentWay) {
    this->currentWay = currentWay;
}

//moves along the map
string Driver::drive() {
     string strCabId =boost::lexical_cast<string>(this->getCab()->getCabId());
    return strCabId;
}
//destructor
Driver::~Driver() {
}

void Driver::setCab(Cab *cab) {
    Driver::cab = cab;
}

Cab *Driver::getCab() const {
    return cab;
}

