
//i want to change to tcp and its very difficult
/*
 this is the main..
from here we run the project
 */
#include <iostream>
#include <stdlib.h>
#include "Parser.h"
#include "Point.h"
#include "Node.h"
#include "PointNode.h"
#include "BfsSearch.h"
#include "Map.h"
#include "TaxiCenter.h"
#include <gtest/gtest.h>
#include "Socket.h"
#include "DriverConect.h"
#include "Clock.h"
#include "Tcp.h"
#include "DriveThread.h"
#include "TripThread.h"
#include "ThreadPool.h"
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
#include <pthread.h>

using namespace std;
using namespace boost::archive;




int checkInput(){
    int input;
    cin>>input;
    if(cin.fail()){
        cin.clear();
        cin.ignore(10000,'\n');
        return (-1);
    }
    cin.clear();
    cin.ignore(10000,'\n');
        return input;
}
int input;
void * driveThread(void * voidDriveThread){
    int cabId;
    int size=0;
    char buffer[4096];
    DriveThread * driveThread1 = (DriveThread *)voidDriveThread;
    TaxiCenter * taxiCenter1 = driveThread1->getTaxiCenter();
    Socket * socket1 = driveThread1->getSocket1();
    DriverConect* driverConect1 =driveThread1->getDriverConect();
    int time = taxiCenter1->getClock()->getTime()+1;
    while(true){
        if (time == taxiCenter1->getClock()->getTime() ) {
            memset(buffer,0, sizeof(buffer));
            string strDriverId = boost::lexical_cast<string>(driverConect1->getDriverId());
            socket1->sendData(strDriverId, driverConect1->getSocketNum());
            socket1->reciveData(buffer, sizeof(buffer), driverConect1->getSocketNum());
            cabId = boost::lexical_cast<int>(buffer);
            taxiCenter1->moveCab(cabId);
            size = taxiCenter1->getCabById(cabId)->getCurrentWay().size()-1;
            time++;
        }
        if (size!= 0 && taxiCenter1->getCabById(cabId)->getLocation() ==
                                 taxiCenter1->getCabById(cabId)->getCurrentWay()[size]){
            break;
        }
        if (input == 7){
            delete driveThread1;
            pthread_exit(NULL);
        }
    }
}

void* tripThread(void* voidtrip){
    TripThread * tripThrea =(TripThread*) voidtrip;
    TaxiCenter *tax= tripThrea->getTax();
    tax->createTrip(tripThrea->getTripId(),tripThrea->getStartPoint().getX(),tripThrea->getStartPoint().getY(),
    tripThrea->getEndPoint().getX(),tripThrea->getEndPoint().getY(),tripThrea->getNumOfPassengers(),
                    tripThrea->getTarrif(),tripThrea->getTime());
    //delete tripThrea;
}
//function that handles the input
void getInput(TaxiCenter * taxiCenter, int port) {
    vector<pthread_t> threadPool;
    Parser parse(taxiCenter);
    ThreadPool * tp = new ThreadPool(5);
    int driverId, cabId, rideId, xStart, yStart, xEnd, yEnd, numPassengers, taxiType, index, time, numOfDrivers;
    char comma, manufacturer, color, buffer[4096];
    double tarrif;
    Trip *trip1;
    Clock * clock = new Clock();
    taxiCenter->setClock(clock);
    Socket * socket1 = new Tcp(1,port);
    socket1->initialize();

    //get input from the user and do missions until we get 7
    do {
        input=checkInput();
        switch (input) {
            case 1: {
                numOfDrivers = checkInput();
                if (numOfDrivers == -1) {
                    cout << numOfDrivers << endl;
                    break;
                }
                for (int i = 0; i < numOfDrivers; i++) {
                    int clientSd = socket1->acceptConnect();
                    socket1->reciveData(buffer, sizeof(buffer), clientSd);
                    driverId = atoi(buffer);
                    DriverConect driverConect(driverId, clientSd);
                    taxiCenter->hireDriver(driverConect);
                    string serial_str;
                    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
                    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
                    boost::archive::binary_oarchive oa(s);
                    oa << taxiCenter->getCabs()[i];
                    s.flush();
                    socket1->sendData(serial_str, driverConect.getSocketNum());
                }
            }
                break;
            case 2:{
                string s;
                getline(cin,s);
                if(!parse.validateTrip(s)){
                    cout<< -1<<endl;
                    break;
                }
                vector<string> strs;
                //empty whitespace in beginning of string
                boost::algorithm::trim_left(s);
                boost::split(strs, s, boost::is_any_of(","));
                //cast string to type needed
                rideId = boost::lexical_cast<int>(strs[0]);
                xStart = boost::lexical_cast<int>(strs[1]);
                yStart = boost::lexical_cast<int>(strs[2]);
                xEnd = boost::lexical_cast<int>(strs[3]);
                yEnd = boost::lexical_cast<int>(strs[4]);
                numPassengers = boost::lexical_cast<int>(strs[5]);
                tarrif = boost::lexical_cast<double>(strs[6]);
                time = boost::lexical_cast<int>(strs[7]);
                TripThread * tripThread1 = new TripThread(taxiCenter,rideId,Point(xStart,yStart),Point(xEnd,yEnd),
                numPassengers,tarrif,time);
                Task * task = new Task(tripThread,tripThread1);
                tp->add_task(task);

                break;
                }

            case 3: {
                string st;
                getline(cin, st);
                if (!parse.validateCab(st)) {
                    cout << -1 << endl;
                    break;
                }
                break;
            }
            case 4: {
                driverId= checkInput();
                if (driverId == -1) {
                    cout << driverId << endl;
                    break;
                }
                bool exist=false;
                for (int i = 0; i < taxiCenter->getDriversId().size(); ++i) {
                    if (taxiCenter->getDriversId()[i].getDriverId() == driverId) {
                        //index = i;
                        exist=true;
                        socket1->sendData(boost::lexical_cast<string>(taxiCenter->getDriversId()[i].getDriverId()),
                                          taxiCenter->getDriversId()[i].getSocketNum());
                        socket1->reciveData(buffer, sizeof(buffer), taxiCenter->getDriversId()[i].getSocketNum());
                        cout << *taxiCenter->getCabById(atoi(buffer))->getLocation();
                    }
                }
                if (!exist){
                    cout << -1 << endl;
                }
                break;
            }
            case 7:{
                break;
            }
            case 9:
                clock->advance();
                for (int i = 0; i < taxiCenter->getTrips().size(); ++i) {
                    if (clock->getTime() == taxiCenter->getTrips()[i]->getTime()) {
                        for (int j = 0; j < taxiCenter->getCabs().size(); ++j) {
                            if (taxiCenter->getCabs()[j]->getLocation()->getPoint() ==
                                taxiCenter->getTrips()[i]->getStartPoint() &&
                                !(taxiCenter->getCabs()[j]->isInDrive())) {
                                string strDriverId = boost::lexical_cast<string>(
                                        taxiCenter->getDriversId()[j].getDriverId());
                                socket1->sendData(strDriverId, taxiCenter->getDriversId()[j].getSocketNum());
                                socket1->reciveData(buffer, sizeof(buffer),
                                                    taxiCenter->getDriversId()[j].getSocketNum());
                                cabId = boost::lexical_cast<int>(buffer);
                                if (cabId != taxiCenter->getCabs()[j]->getCabId()) {
                                    for (int k = 0; k < taxiCenter->getCabs().size(); ++k) {
                                        strDriverId = boost::lexical_cast<string>(
                                                taxiCenter->getDriversId()[k].getDriverId());
                                        socket1->sendData(strDriverId, taxiCenter->getDriversId()[k].getSocketNum());
                                        socket1->reciveData(buffer, sizeof(buffer),
                                                            taxiCenter->getDriversId()[k].getSocketNum());
                                        cabId = boost::lexical_cast<int>(buffer);
                                        if (cabId == taxiCenter->getCabs()[j]->getCabId()) {
                                            j = k;
                                            k = taxiCenter->getCabs().size();
                                        }

                                    }
                                }
                                taxiCenter->assignCabAndTrip(cabId, i);
                                DriveThread *driveThread1 = new DriveThread(taxiCenter->getDriverByIndex(j), taxiCenter,
                                                                            socket1);
                                pthread_t dThread;
                                pthread_create(&dThread, NULL, driveThread, driveThread1);
                                threadPool.push_back(dThread);
                                j = taxiCenter->getCabs().size();
                            }
                        }
                    }
                }


                break;
            default: {
                cout << -1 << endl;
                break;
            }
        }

        usleep(10000);
    } while (input != 7);
    for (int l = 0; l < threadPool.size(); ++l) {
        pthread_join(threadPool[l],NULL);
    }
    for (int i = 0; i < numOfDrivers; ++i) {
        socket1->sendData("close", taxiCenter->getDriversId()[i].getSocketNum());
    }
    delete socket1;
    delete clock;
    delete tp;
}

//main: the function that runs the project
int main(int argc, char **argv) {
    string s;
    int port= atoi(argv[1]);
    Map *map = new Map(0, 0);
    TaxiCenter *taxiCenter = new TaxiCenter(map);
    Parser pa(taxiCenter);
    getline(cin,s);
    while(!pa.validateMap(s)){
        cout<<-1<<endl;
        getline(cin,s);
    }

    getInput(taxiCenter, port);
    delete map;
    delete taxiCenter;
    return 0;
}