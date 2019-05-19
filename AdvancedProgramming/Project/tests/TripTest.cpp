
#include <gtest/gtest.h>
#include "../Trip.h"

/**
 * class of test Trip inherits from gtest, and responsible
 * for testing Trip's methods
 */

class TripTest: public::testing::Test {

protected:
    Trip *trip1;
    //setting up a taxi center
    virtual void SetUp() {
        trip1 = new Trip(0,0,0,2,2,3,80);
    }
    //deletes the allocated memory for the points after every test
    virtual void TearDown(){
        delete trip1;
    }
};

//tests if the tariff is calculated proparly
TEST_F(TripTest,calculateTarrif) {

    ASSERT_EQ(0,trip1->calculateTarrif());
}
