//
// Created by noam on 12/01/17.
//

#include "DriverConect.h"

DriverConect::DriverConect() {}

DriverConect::~DriverConect() {

}

DriverConect::DriverConect(int driverId, int socketNum) : driverId(driverId), socketNum(socketNum) {}

int DriverConect::getDriverId() const {
    return driverId;
}

int DriverConect::getSocketNum() const {
    return socketNum;
}
