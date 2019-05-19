//
// Created by noam on 17/01/17.
//

#ifndef MISSION2_TRIPTHREAD_H
#define MISSION2_TRIPTHREAD_H


#include "TaxiCenter.h"
#include "TaxiCenter.h"
#include "Trip.h"

class TripThread {
private:
    TaxiCenter* tax;
public:
    TaxiCenter *getTax() const;

public:
    int getTripId() const;

    const Point &getStartPoint() const;

    const Point &getEndPoint() const;

    int getNumOfPassengers() const;

    double getTarrif() const;

    int getTime() const;

private:
    int tripId;
    Point startPoint;
    Point endPoint;
    int numOfPassengers;
    double tarrif;
    int time;
public:

    TripThread(TaxiCenter *tax, int tripId, const Point &startPoint, const Point &endPoint, int numOfPassengers,
               double tarrif, int time);

    virtual ~TripThread();

    void setTax(TaxiCenter *tax);
};



#endif //MISSION2_TRIPTHREAD_H
