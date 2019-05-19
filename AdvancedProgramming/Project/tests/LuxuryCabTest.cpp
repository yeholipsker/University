
#include <gtest/gtest.h>
#include "../LuxuryCab.h"
#include "BfsSearchTest.h"

/**
 * class of test LuxuryCab inherits from gtest, and responsible
 * for testing LuxuryCab's methods
 */

class LuxuryCabTest: public BfsSearchTest {

protected:
    LuxuryCab *luxcab;
    vector<PointNode*> path;
    //setting up a taxi center
    virtual void SetUp() {
        BfsSearchTest::SetUp();
        luxcab = new LuxuryCab(0,'S','G',this->map3->getNode(Point(0,0)));
        for (int i = 0; i < v.size(); ++i) {
            path.push_back(this->map3->getNode(v[i]));
        }
    }
    //deletes the allocated memory for the points after every test
    virtual void TearDown(){
        BfsSearchTest::TearDown();
        delete luxcab;
    }


};
//tests if move func works properly
TEST_F(LuxuryCabTest,move) {
    luxcab->move(path,map3->getNode(Point(0,0)));
    EXPECT_FALSE(luxcab->getLocation() == map3->getNode(Point(0,1)));
    ASSERT_TRUE(luxcab->getLocation() == map3->getNode(Point(0,2)));
}
