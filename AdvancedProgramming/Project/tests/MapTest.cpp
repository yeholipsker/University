
#include "MapTest.h"

using namespace std;

/**
 * class of test Map. inherits from gtest, and responsible
 * for testing Map's methods
 */

//setting up three maps
     void  MapTest:: SetUp() {
        map1 = new Map(1, 1);
        map2 = new Map(2, 1);
        map3 = new Map(3, 3);
    }
//deletes the allocated memory for the points after every test
     void MapTest:: TearDown(){
        delete map1;
        delete map2;
        delete map3;
    }

//checks if grid is created properly
TEST_F(MapTest, createTheGrid) {

    EXPECT_EQ(map1->getNode(Point(0,0)), map1->getGrid()[0][0]);

}

