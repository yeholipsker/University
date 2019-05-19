#include "Map.h"
#include "Driver.h"
#include "Cab.h"
#include "Trip.h"
#include "vector"
#include "DriverConect.h"
#include "Clock.h"

#ifndef MISSION2_TAXICENTER_H
#define MISSION2_TAXICENTER_H


class TaxiCenter {

private:
    Map * map;
    Clock * clock;
public:
    Clock *getClock() const;

    void setClock(Clock *clock);

private:
    vector<DriverConect> driversId;
    vector<Trip*> trips;
    vector<Cab*> cabs;
public:
    const vector<Cab *> &getCabs() const;

public:
    //constructor
    TaxiCenter(Map * map);
    //destructor
    ~TaxiCenter();
    //hires a driver
    void hireDriver(DriverConect driverC);

    //buys a cab
    void buyCab(int cabId, int taxiType, char manufacturer, char color);

    //creates a trip
    void createTrip(int rideId, int xStart, int yStart, int xEnd, int yEnd, int numPassengers, double tarrif, int time);

    //creates a trip
    void createTrip(Trip *trip);


    //returns the drivers in the taxi center
    vector<DriverConect> getDriversId();

    //gets driver by id
    DriverConect* getDriverByIndex(int index);

    //returns the trips in the taxi center
    vector<Trip*> getTrips();

    //assign available cab to a trip and ready it for a ride
    void assignCabAndTrip(int cabId,int tripIndex);

    //move the cab to its next location
    void moveCab(int cabId);
    

    Cab * getCabById(int cabId);
    void addtrip(Trip *trip);

    Map *getMap();

    void setMap(Map *map);
};


#endif //MISSION2_TAXICENTER_H
//