
#include "TaxiCenter.h"
#include "LuxuryCab.h"
#include "PointNode.h"
#include <algorithm>

//hires a driver
void TaxiCenter::hireDriver(DriverConect driverc){
    this->driversId.push_back(driverc);
}

//buys a cab
void TaxiCenter::buyCab(int cabId, int taxiType, char manufacturer, char color){
    Cab * cab;
    if (taxiType == 1) {
        cab = new Cab(cabId,manufacturer,color,this->map->getNode(Point(0,0)));
    }
    if (taxiType == 2) {
        cab = new LuxuryCab(cabId,manufacturer,color,this->map->getNode(Point(0,0)));
    }
    this->cabs.push_back(cab);
}

//creates a trip


void TaxiCenter:: createTrip(int rideId, int xStart, int yStart, int xEnd, int yEnd, int numPassengers, double tarrif,
                             int time){

    Point point1(xStart, yStart);
    Point point2(xEnd,yEnd);
    Trip * trip = new Trip(rideId, point1,point2,numPassengers,tarrif, time);
    BfsSearch bfsSearch(this->map->getNode(point1));
    vector<Node*> temp = bfsSearch.findTheWay(this->map->getNode(point2));
    vector<PointNode*> path;
    for (int i = 0; i < temp.size(); ++i) {
        path.push_back(this->map->getNode(temp[i]));
    }
    trip->setPath(path);
    this->trips.push_back(trip);
    this->map->resetFathers();
}

//creates a trip

void TaxiCenter:: createTrip(Trip* trip){
    int index;
    for (int j = 0; j <this->getTrips().size() ; ++j) {
        if(trip->getTripId()==this->getTrips()[j]->getTripId()){
            index=j;
            break;
        }
    }
    BfsSearch bfsSearch(this->map->getNode(this->getTrips()[index]->getStartPoint()));
    vector<Node*> temp = bfsSearch.findTheWay(this->map->getNode(this->getTrips()[index]->getEndPoint()));
    vector<PointNode*> path;
    for (int i = 0; i < temp.size(); ++i) {
        path.push_back(this->map->getNode(temp[i]));
    }
    this->getTrips()[index]->setPath(path);
    this->map->resetFathers();
}
//returns the drivers in the taxi center
vector<DriverConect> TaxiCenter::getDriversId(){

    return this->driversId;
}

//returns the trips in the taxi center
vector<Trip*> TaxiCenter::getTrips(){
    return this->trips;
}

//constructor
TaxiCenter::TaxiCenter(Map *map) {
    this->map = map;
}

//destructor
TaxiCenter::~TaxiCenter() {
    this->driversId.clear();
    for (int i = 0; i < this->cabs.size(); ++i) {
        delete this->cabs[i];
    }
    this->cabs.clear();
    for (int i = 0; i < this->trips.size(); ++i) {
        delete this->trips[i];
    }
    this->trips.clear();
}

//assign available cab to a trip and ready it for a ride
void TaxiCenter::assignCabAndTrip(int cabId,int tripIndex) {
    int index;
    for (int i = 0; i < this->cabs.size(); ++i) {
        if (this->cabs[i]->getCabId() == cabId) {
            index = i;
            break;
        }
    }
    this->cabs[index]->setCurrentWay(this->trips[tripIndex]->getPath());
    this->cabs[index]->setLocation(this->trips[tripIndex]->getPath()[0]);
    this->cabs[index]->setInDrive(true);
}

void TaxiCenter::moveCab(int cabId) {
    int index;
    for (int i = 0; i < this->cabs.size(); ++i) {
        if (this->cabs[i]->getCabId() == cabId) {
            index = i;
            break;
        }
    }
    PointNode * location = this->cabs[index]->getLocation();
    vector<PointNode *> path = this->cabs[index]->getCurrentWay();
    this->cabs[index]->move(path,location);
    if (this->cabs[index]->getLocation()->getPoint() == path[path.size()-1]->getPoint()) {
        this->cabs[index]->setInDrive(false);
    }
}

Cab *TaxiCenter::getCabById(int cabId) {
    for (int i = 0; i < this->cabs.size(); ++i) {
        if (this->cabs[i]->getCabId() == cabId) {
            return this->cabs[i];
        }
    }
    return NULL;
}

Clock *TaxiCenter::getClock() const {
    return clock;
}

void TaxiCenter::setClock(Clock *clock) {
    TaxiCenter::clock = clock;
}

const vector<Cab *> &TaxiCenter::getCabs() const {
    return cabs;
}

DriverConect* TaxiCenter::getDriverByIndex(int index) {
    return &this->driversId[index];
}

void TaxiCenter:: addtrip(Trip *trip){
    this->trips.push_back(trip);
}

Map *TaxiCenter::getMap() {
    return map;
}

void TaxiCenter::setMap(Map *map) {
    TaxiCenter::map = map;
}
