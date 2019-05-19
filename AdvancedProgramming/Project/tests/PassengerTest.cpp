/**
 * class of test passanger inherits from gtest, and responsible
 * for testing passanger's methods
 */

#include <gtest/gtest.h>
#include "../Passanger.h"
//tests if the random function works properly
TEST(PassengerTest, TestRndomness) {
    Passanger passanger;
    int rand = passanger.randSatisfaction();
    ASSERT_LE(rand,5);
    ASSERT_GE(rand,1);
}