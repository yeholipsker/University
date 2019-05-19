/*
 *trop class. responsible for trip member.
 * holds all of the members and functions trip needs
 */

#ifndef MISSION2_TRIP_H
#define MISSION2_TRIP_H


#include "Point.h"
#include "PointNode.h"
#include "BfsSearch.h"

class Trip {
private:
    int tripId;
    int meterPassed;
    Point startPoint;
    Point endPoint;
    int numOfPassengers;
    int time;
public:
    const Point &getStartPoint() const;

private:
    double tarrif;
    vector<PointNode*> path;

public:

    //constructor for case of ints instead of Points
    Trip(int tripid, int startX,int startY, int endX, int endY, int numOfPassengers, double tarrif, int time);

    //constructor in case of points
    Trip(int tripid,Point start,Point end, int numOfPassengers, double tarrif, int time);

    //destructor
    ~Trip();


    //set and get functions for the different type of vriables this class is initialized with

    void setPath(vector<PointNode*> path);

    int getTripId() const;

    //calculates the taarif of the trip
    double calculateTarrif();

    //get the path of the trip
    const vector<PointNode *> &getPath() const;

    //get the time of the trip
    int getTime() const;

    Point getEndPoint(){ return this->endPoint;}

    bool operator <(const Trip& trip1);

};


#endif //MISSION2_TRIP_H
