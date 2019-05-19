/**
 * this class is responsible for the managment of all drivers in the programs
 */
#include "DriversCenter.h"


//destructor
DriversCenter::~DriversCenter(){
    for (int i = 0; i < this->drivers.size(); ++i) {
        delete this->drivers[i]->getCab()->getLocation();
        delete this->drivers[i]->getCab();
        delete this->drivers[i];
    }
    this->drivers.clear();
}
//hires a driver
void DriversCenter::hireDriver(int driverId, int age, char status, int experience, int cabId){

    Driver * driver = new Driver(driverId, age, status, cabId, experience);
    this->drivers.push_back(driver);

}

 //returns the drivers in the Driverscenter
vector<Driver*> DriversCenter:: getDrivers(){
    return this->drivers;
}
