//
// Created by yehoshua on 15/01/17.
//

#ifndef MISSION2_DRIVETHREAD_H
#define MISSION2_DRIVETHREAD_H


#include "TaxiCenter.h"
#include "Socket.h"

class DriveThread {
public:
    DriveThread(DriverConect *driverConect, TaxiCenter *taxiCenter, Socket *socket1);

    TaxiCenter *getTaxiCenter() const;

    void setTaxiCenter(TaxiCenter *taxiCenter);

    DriverConect *getDriverConect() const;

    void setDriverConect(DriverConect *driverConect);

private:
    DriverConect * driverConect;
    TaxiCenter * taxiCenter;
    Socket * socket1;
public:
    Socket *getSocket1() const;

    void setSocket1(Socket *socket1);
};


#endif //MISSION2_DRIVETHREAD_H
