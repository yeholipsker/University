#include <gtest/gtest.h>
#include "../Point.h"
#include "../PointNode.h"
#include "MapTest.h"

/**
 * class of test point. inherits from gtest, and responsible
 * for testing Point's methods
 */
class PointNodeTest:public MapTest {
protected:
    PointNode * p1;
    PointNode * p2;
    PointNode * p3;
    //setting up three points
    virtual void SetUp() {
        MapTest::SetUp();
        p1 = map3->getNode(Point(1,2));
    }
    //deletes the allocated memory for the points after every test
    virtual void TearDown(){
        MapTest::TearDown();
    }
};

//test the operator overloading on <<.
TEST_F(PointNodeTest,operatorOverloadingPrint) {
    stringstream buffer;
    buffer << p1->getPoint();
    ASSERT_EQ("(1,2)\n",buffer.str());
}
//test getNeighbors()
TEST_F(PointNodeTest,getNeighbors) {
    vector<Node*> v = p1->getNeighbors();
    ASSERT_EQ(map3->getNode(Point(0,2)),v[0]);
    ASSERT_EQ(map3->getNode(Point(2,2)),v[1]);
    ASSERT_EQ(map3->getNode(Point(1,1)),v[2]);
}