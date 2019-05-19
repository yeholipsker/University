
#include <iostream>
#include "DriversCenter.h"
#include "Cab.h"
#include "Socket.h"
#include "Tcp.h"
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;
using namespace boost::archive;



//get input from the user
void getInput(DriversCenter * driversCenter) {
    int input, driverId, age, experience, cabId;
    char comma, status;
    cin >> driverId >> comma >> age >> comma >> status >> comma >> experience >> comma >> cabId;
    driversCenter->hireDriver(driverId, age, status, experience, cabId);
}

int stringToInt(char * s){
    return atoi(s);
}

//main function of client

int main(int argc, char **argv) {

    int port = atoi(argv[2]);
    char buffer[4096];
    Socket* udp;
    udp= new Tcp(false,port);
    udp->initialize();
    DriversCenter *driversCenter =new DriversCenter();
    getInput(driversCenter);
    for (int i=0;i<driversCenter->getDrivers().size();i++) {
        udp->sendData(boost::lexical_cast<string>(driversCenter->getDrivers().at(i)->getId()),0);
    }

    for (int j=0;j<driversCenter->getDrivers().size();j++) {

        Cab * cab;
        udp->reciveData(buffer, sizeof(buffer),0);
        string str(buffer, sizeof(buffer));
        boost::iostreams::basic_array_source<char> device(str.c_str(), str.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        ia >> cab;
        driversCenter->getDrivers()[j]->setCab(cab);

    }
    int drivnum;
    udp->reciveData(buffer, sizeof(buffer),0);
    string bufferStr(buffer);
    while (bufferStr.compare("close") != 0)
     {
        for (int k = 0; k < driversCenter->getDrivers().size(); ++k) {
            if (driversCenter->getDrivers().at(k)->getId()
                == stringToInt(buffer)) {
                drivnum = k;
            }
        }
        udp->sendData(driversCenter->getDrivers().at(drivnum)->drive(),0);
         udp->reciveData(buffer, sizeof(buffer),0);
         bufferStr.assign(buffer);
    }
    delete udp;
    delete driversCenter;
    return 0;
}



