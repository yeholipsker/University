//
// Created by noam on 17/01/17.
//

#include "TripThread.h"

TripThread::~TripThread() {

}

TripThread::TripThread(TaxiCenter *tax, int tripId, const Point &startPoint, const Point &endPoint, int numOfPassengers,
                       double tarrif, int time) : tax(tax), tripId(tripId), startPoint(startPoint), endPoint(endPoint),
                                                  numOfPassengers(numOfPassengers), tarrif(tarrif), time(time) {}

int TripThread::getTripId() const {
    return tripId;
}

const Point &TripThread::getStartPoint() const {
    return startPoint;
}

const Point &TripThread::getEndPoint() const {
    return endPoint;
}

int TripThread::getNumOfPassengers() const {
    return numOfPassengers;
}

double TripThread::getTarrif() const {
    return tarrif;
}

int TripThread::getTime() const {
    return time;
}

TaxiCenter *TripThread::getTax() const {
    return tax;
}
