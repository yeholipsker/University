//
// Created by yehoshua on 30/01/17.
//

#ifndef MISSION2_CLIENTPARSER_H
#define MISSION2_CLIENTPARSER_H


#include "DriversCenter.h"

class ClientParser {
private:
    DriversCenter * driversCenter;
public:
    ClientParser(DriversCenter * driversCenter);
    bool validateDriver();
};


#endif //MISSION2_CLIENTPARSER_H
