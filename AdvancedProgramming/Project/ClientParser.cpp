//
// Created by yehoshua on 30/01/17.
//

#include "ClientParser.h"

ClientParser::ClientParser(DriversCenter *driversCenter) {
    this->driversCenter = driversCenter;
}
static bool checkNumber(string s){
    for (int i = 0; i < s.size(); ++i) {
        if (!isdigit(s.at(i))){
            return false;
        }
    }
    return true;
}

bool ClientParser::validateDriver() {
    int driverId, age, experience, cabId;
    char status;
    string s;
    getline(cin,s);
    vector<string> strs;
    boost::algorithm::trim_left(s);
    boost::split(strs,s,boost::is_any_of(","));
    //if there are incompatible number of inputs
    if (strs.size() != 5) {
        return false;
    }
    for (int i = 0; i < strs.size(); ++i) {
        if (i != 2){
            //if one of the numbers is not integer or negative
            if (!checkNumber(strs[i])) {
                return false;
            }
        }

    }
    //if it's non-included type
    if (strs[2].compare("S") != 0 && strs[2].compare("M") != 0 && strs[2].compare("D") != 0 &&
        strs[2].compare("W") != 0 ) {
        return false;
    }
    driverId = boost::lexical_cast<int>(strs[0]);
    age = boost::lexical_cast<int>(strs[1]);
    status = boost::lexical_cast<char>(strs[2]);
    experience = boost::lexical_cast<int>(strs[3]);
    cabId = boost::lexical_cast<int>(strs[4]);
    driversCenter->hireDriver(driverId,age,status,experience,cabId);
}