//
// Created by yehoshua on 29/12/16.
//

#ifndef MISSION2_CLOCK_H
#define MISSION2_CLOCK_H

/**
 * class clock, handles the advance of time in the world, and can tell us what
 * 'time' is..
 */
class Clock {

private:
    //members
    int time;

public:
    //constructor
    Clock();
    //this function tells the clock to advance the timer
    void advance();
    // getter for the time
    int getTime() const;
    //destructor
    ~Clock();
};


#endif //MISSION2_CLOCK_H
