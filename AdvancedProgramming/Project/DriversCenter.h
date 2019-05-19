/**
 * this class is responsible for the managment of all drivers in the programs
 */

#ifndef MISSION2_DRIVERSCENTER_H
#define MISSION2_DRIVERSCENTER_H

#include "Driver.h"


class DriversCenter {

//members

private:
    vector<Driver*> drivers;

public:

    //def ctor
    DriversCenter(){}

    //destructor
    ~DriversCenter();
    //hires a driver
    void hireDriver(int driverId, int age, char status, int experience, int cabId);

    //returns the drivers in the Driverscenter
    vector<Driver*> getDrivers();
};


#endif //MISSION2_DRIVERSCENTER_H
