/**
 * class of test BfsSearch inherits from Maptest, and responsible
 * for testing BfsSearch's methods
 */
#include "BfsSearchTest.h"
    //setting up so it can start the tests
    void  BfsSearchTest::SetUp() {
        MapTest::SetUp();
        Point start(0,0);
        Point end(2,2);
        Node * nodeStart;
        Node * nodeEnd;
        nodeStart = map3->getNode(start);
        nodeEnd = map3->getNode(end);
        BfsSearch bfsSearch(nodeStart);
        v = bfsSearch.findTheWay(nodeEnd);
    }

    //deletes all the allocated memory
    void BfsSearchTest::TearDown() {
        MapTest::TearDown();
    }

//checks if the way the bfs finds is the right one
TEST_F(BfsSearchTest,testTheWay) {
    vector<Node*>::iterator it = v.begin();
    ASSERT_EQ(map3->getNode(Point(0,0)), *it);
    ++it;
    ASSERT_EQ(map3->getNode(Point(0,1)), *it);
    ++it;
    ASSERT_EQ(map3->getNode(Point(0,2)), *it);
    ++it;
    ASSERT_EQ(map3->getNode(Point(1,2)), *it);
    ++it;
    ASSERT_EQ(map3->getNode(Point(2,2)), *it);
}