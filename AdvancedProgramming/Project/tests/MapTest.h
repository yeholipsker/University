
#include <gtest/gtest.h>
#include "../Point.h"
#include "../PointNode.h"
#include "../Node.h"
#include "../Map.h"
#ifndef MISSION2_MAPTEST_H
#define MISSION2_MAPTEST_H

/**
 * class of test Map. inherits from gtest, and responsible
 * for testing Map's methods
 */

class MapTest: public::testing::Test {
protected:
    Map *map1, *map2, *map3;
public:
    //setting up the maps
    virtual  void SetUp();
    //deletes the allocated memory for the points after every test
    virtual void TearDown();

};
#endif //MISSION2_MAPTEST_H
