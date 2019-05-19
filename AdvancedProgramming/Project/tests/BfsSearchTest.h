//
// Created by yehoshua on 14/12/16.
//
#include "MapTest.h"
#include "../BfsSearch.h"
#ifndef MISSION2_BFSSEARCHTEST_H
#define MISSION2_BFSSEARCHTEST_H

class BfsSearchTest: public MapTest {
protected:
    vector<Node*> v;
    virtual void  SetUp();
    virtual void TearDown();
};
#endif //MISSION2_BFSSEARCHTEST_H
