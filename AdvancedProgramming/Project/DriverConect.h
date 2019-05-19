//
// Created by noam on 12/01/17.
//

#ifndef MISSION2_DRIVERCONECT_H
#define MISSION2_DRIVERCONECT_H


class DriverConect {
private:
    int driverId;
    int socketNum;
public:
    DriverConect();

    DriverConect(int driverId, int socketNum);

    virtual ~DriverConect();

    int getDriverId() const;

    int getSocketNum() const;
};


#endif //MISSION2_DRIVERCONECT_H
