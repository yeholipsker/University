/*
 * this class is responsible for all what a driver member needs.
 * it holds all of his data,
 */
#ifndef MISSION2_DRIVER_H
#define MISSION2_DRIVER_H


#include "Cab.h"
#include "Passanger.h"
#include <vector>
#include "Trip.h"
#include "BfsSearch.h"
#include<string>
class Driver {
private:
    enum MaritalStatus{SINGLE,MARRIED,DIVORCED,WIDOWED};
    //members
    int id;
    int cabId;
    int age;
    MaritalStatus status;
    int experience;
    float avgSatisfaction;
    Cab * cab;
public:
    Cab *getCab() const;

public:
    void setCab(Cab *cab);

private:
    vector<Passanger> listOfPassengers;
    vector<PointNode *> currentWay;

private:
    int sumSatisfaction;
    int sumCustomers;
    PointNode * location;

public:

    //constructor
    Driver(int id, int age,char maritialStatus, Cab * cab, int experience, PointNode* location);
    Driver(int id, int age,char maritialStatus, int  cabId, int experience):
            id(id), age(age), cabId(cabId), experience(experience){}

    //destructor
    ~Driver();

    //gets the id
    int getId();

    //gets the location of the driver
    PointNode *getLocation() const;

    //sets the location of the driver
    void setLocation(PointNode *location);

    //sets the way
    void setCurrentWay(const vector<PointNode *> &currentWay);

    //moves along the map
    string drive();

};


#endif //MISSION2_DRIVER_H
