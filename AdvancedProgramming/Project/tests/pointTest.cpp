#include <gtest/gtest.h>
#include "../Point.h"

/**
 * class of test point. inherits from gtest, and responsible
 * for testing Point's methods
 */
class PointTest:public::testing::Test {
protected:
    Point * p1;
    Point * p2;
    Point * p3;
    //setting up three points
    virtual void SetUp() {
        p1 = new Point(0, 2);
        p2 = new Point(1, 2);
        p3 = new Point(1, 2);
    }
    //deletes the allocated memory for the points after every test
    virtual void TearDown(){
        delete p1;
        delete p2;
        delete p3;
    }
};

//test the operator overloading on ==.
TEST_F(PointTest,operatorOverloadingEqual) {
    ASSERT_FALSE(*p1==*p2);
    ASSERT_EQ(*p2,*p3);
}
//test the operator overloading on <<.
TEST_F(PointTest,operatorOverloadingPrint) {
    stringstream buffer;
    buffer << *p1;
    ASSERT_EQ("(0,2)\n",buffer.str());
}
//test getX() and getY().
TEST_F(PointTest,getters) {
    ASSERT_NE(p1->getX(),p1->getY());
    ASSERT_EQ(p2->getX(),p3->getX());
    ASSERT_TRUE(p1->getY() == p3->getY());
}