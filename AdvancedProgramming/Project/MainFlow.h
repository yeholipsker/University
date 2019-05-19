/*
 * this class is responsible for initlizing the program.
 * it creates the map and the taxi station.
 */
//
#ifndef MISSION2_MAINFLOW_H
#define MISSION2_MAINFLOW_H
#include "TaxiCenter.h"
#include "Map.h"
#include "Statistics.h"

class MainFlow {
private:
Statistics *stat;
    Map *map;
    TaxiCenter *tax;

public:
//constructor
MainFlow();

    //destructor
    ~MainFlow();

    //create a taxicenter
    TaxiCenter* createTaxiCenter();

    //create a map
    Map* createMap();

};


#endif //MISSION2_MAINFLOW_H
