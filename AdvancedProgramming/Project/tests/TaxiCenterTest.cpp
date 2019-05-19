#include "../Map.h"
#include "../Driver.h"
#include "../Cab.h"
#include "../Trip.h"
#include "vector"
#include <gtest/gtest.h>
#include "../TaxiCenter.h"
#include "MapTest.h"

/**
 * class of test taxicenter inherits from gtest, and responsible
 * for testing TaxiCenter's methods
 */

class TaxiCenterTest: public MapTest {

protected:
    TaxiCenter *tax1;
    //setting up a taxi center
    virtual void SetUp() {
        MapTest::SetUp();
        tax1 = new TaxiCenter(this->map3);
        tax1->buyCab(0,1,'S','G');
        tax1->hireDriver(0,28,'m',3,0);
        tax1->createTrip(0,0,0,2,2,3,4.5);
    }
    //deletes the allocated memory for the points after every test
    virtual void TearDown(){
        MapTest::TearDown();
        delete tax1;
    }
};
    //tests if hired a driver, if this is the first hired taxi
    TEST_F(TaxiCenterTest,hiredriver) {
        ASSERT_FALSE(tax1->getDrivers().empty());
        ASSERT_EQ(0, tax1->getDrivers().front()->getId());

    }
    //tests if bought a cab
    TEST_F(TaxiCenterTest,buycab) {
    ASSERT_FALSE(tax1->getCabss().empty());
        ASSERT_EQ(0, tax1->getCabss().front()->getCabId());

    }
    //test if created a trip
    TEST_F(TaxiCenterTest,createtrip) {
    ASSERT_FALSE(tax1->getTrips().empty());
        ASSERT_EQ(0, tax1->getTrips().front()->getTripId());

    }