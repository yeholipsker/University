/*
 * this class is responsible for initializing the program.
 * it creates the map and the taxi station.
 */
//
#include "MainFlow.h"

//constructor
MainFlow::MainFlow(){

    map=NULL;
    tax=NULL;
    stat=NULL;
}

//destructor
MainFlow::~MainFlow(){
    if(this->map != NULL){
        delete this->map;
    }
    if (this->tax != NULL) {
        delete this->tax;
    }
}

//create a taxi center
TaxiCenter* MainFlow:: createTaxiCenter(){
    tax=new TaxiCenter(this->map);
    return tax;
}

//create a map
Map* MainFlow:: createMap(){
    map=new Map(0,0);
    return map;
}
