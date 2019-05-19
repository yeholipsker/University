
/*
 * passanger class. this class is responsible of the passenger member
 * it holds all the data about the passenger and has functions that passenger needs
 */

#include "Point.h"
#ifndef MISSION2_PASSANGER_H
#define MISSION2_PASSANGER_H
//

class Passanger {

private:
    Point sourcePoint;
    Point destinationPoint;

public:

    //makes a random satisfaction result
    int randSatisfaction();

    //returns the source point of the trip
    Point getSourcePoint();

    //returns destination point of the trip for this passenger
    Point getDestinationPoint();

};


#endif //MISSION2_PASSANGER_H
