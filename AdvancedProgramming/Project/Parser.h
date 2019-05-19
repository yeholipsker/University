//this class checks the input from user, and inserts it to the program.

#include "Trip.h"
#include "Cab.h"
#include "TaxiCenter.h"
#include "Point.h"
#include "Map.h"

#ifndef MISSION2_PARSER_H
#define MISSION2_PARSER_H


class Parser {
private:

    TaxiCenter* taxi;

public:
    Parser(TaxiCenter *taxi);

    bool validateTrip(string s);
    bool validateCab(string s);
    bool validateMap(string s);
    bool checkObsticale(string s,int maxX,int maxY);
};


#endif //MISSION2_PARSER_H
