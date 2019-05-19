//
// Created by yehoshua on 29/12/16.
//

#include "Clock.h"

//constructor
Clock::Clock() {
    this->time = 0;
}

// getter for the time
int Clock::getTime() const {
    return time;
}

//destructor
Clock::~Clock() {
}

//this function tells the clock to advance the timer
void Clock::advance() {
    this->time++;
}
