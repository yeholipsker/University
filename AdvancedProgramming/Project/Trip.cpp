/*
*trop class. responsible for trip member.
* holds all of the members and functions trip needs
*/

#include "Trip.h"


//constructor for case of ints instead of Points
Trip::Trip(int tripid, int startX,int startY, int endX, int endY, int numOfPassengers, double tarrif, int time)
        :tripId(tripid), numOfPassengers(numOfPassengers), tarrif(tarrif), time(time) {

    this->startPoint=Point(startX,startY);
    this->endPoint=Point(endX,endY);
}

//constructor in case of points
Trip::Trip(int tripid,Point start,Point end, int numOfPassengers, double tarrif, int time)
        :tripId(tripid), startPoint(start),endPoint(end),numOfPassengers(numOfPassengers),
         tarrif(tarrif), time(time){
}

//calculates the taarif of the trip
double Trip::calculateTarrif() {
    return 0;
}

int Trip::getTripId() const {
    return this->tripId;
}


void Trip::setPath(vector<PointNode*> path){
    this->path = path;
}

const vector<PointNode *> &Trip::getPath() const {
    return this->path;
}

//destructor
Trip::~Trip() {
}

int Trip::getTime() const {
    return time;
}

bool Trip::operator <(const Trip& trip1) {
    return this->time < trip1.time;
}

const Point &Trip::getStartPoint() const {
    return startPoint;
}
