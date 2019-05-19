
#include <gtest/gtest.h>
#include "../Cab.h"
#include "BfsSearchTest.h"

/**
 * class of test Cab inherits from gtest, and responsible
 * for testing Cab's methods
 */

class CabTest: public BfsSearchTest {

protected:
    Cab *cab;
    vector<PointNode*> path;
    //setting up a taxi center
    virtual void SetUp() {
        BfsSearchTest::SetUp();
        cab = new Cab(0,'S','G',this->map3->getNode(Point(0,0)));
        for (int i = 0; i < v.size(); ++i) {
            path.push_back(this->map3->getNode(v[i]));
        }
    }
    //deletes the allocated memory for the points after every test
    virtual void TearDown(){
        BfsSearchTest::TearDown();
        delete cab;
    }


};
//tests if move func works properly
TEST_F(CabTest,move) {
    cab->move(path,map3->getNode(Point(0,0)));
    ASSERT_FALSE(cab->getLocation() == map3->getNode(Point(1,0)));
    ASSERT_TRUE(cab->getLocation() == map3->getNode(Point(0,1)));
}
