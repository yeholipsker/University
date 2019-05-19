
#include <gtest/gtest.h>
#include "../MainFlow.h"

/**
 * class of test MainFlow inherits from gtest, and responsible
 * for testing MainFlow's methods
 */

class MainFlowTest: public::testing::Test {

protected:
    MainFlow *main1;
    //setting up a taxi center
    virtual void SetUp() {
        main1 = new MainFlow();
    }
    //deletes the allocated memory for the points after every test
    virtual void TearDown(){
        delete main1;
    }


};
//tests if creates a new map
TEST_F(MainFlowTest,createmap) {
    Map *m=main1->createMap();
    ASSERT_FALSE(m==NULL);
}

//tests if creates a new TaxiCenter
TEST_F(MainFlowTest,createtaxicenter) {
    TaxiCenter *t=main1->createTaxiCenter();
    ASSERT_FALSE(t==NULL);
}