//
// Created by yehoshua on 15/01/17.
//

#include "DriveThread.h"

TaxiCenter *DriveThread::getTaxiCenter() const {
    return taxiCenter;
}

void DriveThread::setTaxiCenter(TaxiCenter *taxiCenter) {
    DriveThread::taxiCenter = taxiCenter;
}

DriverConect *DriveThread::getDriverConect() const {
    return driverConect;
}

void DriveThread::setDriverConect(DriverConect *driverConect) {
    DriveThread::driverConect = driverConect;
}

Socket *DriveThread::getSocket1() const {
    return socket1;
}

void DriveThread::setSocket1(Socket *socket1) {
    DriveThread::socket1 = socket1;
}

DriveThread::DriveThread(DriverConect *driverConect, TaxiCenter *taxiCenter, Socket *socket1) : driverConect(
        driverConect), taxiCenter(taxiCenter), socket1(socket1) {}
