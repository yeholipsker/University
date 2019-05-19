/*
 * passanger class. this class is responsible of the passenger member
 * it holds all the data about the passenger and has functions that passenger needs
 */

#include "Passanger.h"
#include <cstdlib>
//makes a random satisfaction result
int Passanger:: randSatisfaction(){
    int rand1 = rand() % 5 + 1;
    return rand1;
}

//returns the source point of the trip
Point Passanger::getSourcePoint(){ return this->sourcePoint;}

//returns destination point of the trip for this passenger
Point Passanger::getDestinationPoint(){ return this->destinationPoint;}