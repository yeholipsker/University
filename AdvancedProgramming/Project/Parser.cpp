
#include "Parser.h"

Parser::Parser(TaxiCenter *taxi) : taxi(taxi) {}


//check if string is a number
static bool checkNumber(string s){
    for (int i = 0; i < s.size(); ++i) {
        if (!isdigit(s.at(i))){
            return false;
        }
    }
    return true;
}
//check if string is a number of double type (for taarif)
bool checkFractionNumber(string s) {
    int flag=0;
    for (int i = 0; i < s.size(); ++i) {
        if (!isdigit(s.at(i))) {
            if ((s.at(i) != '.') || flag!=0) {
                return false;
            }
            flag++;
        }
    }
    return true;
}

//validates input of trip type
    bool Parser::validateTrip(string s) {
        int rideId, xStart, yStart, xEnd, yEnd, numPassengers, time;
        double tarrif;
        vector<string> strs;
    //empty whitespace in beginning of string
        boost::algorithm::trim_left(s);
        boost::split(strs, s, boost::is_any_of(","));

        //if there are incompatible number of inputs
        if (strs.size() != 8) {
            return false;
        }
        for (int i = 0; i < strs.size(); ++i) {

            //if one of the numbers is not integer or negative
            if (!checkFractionNumber(strs[i])) {
                return false;
            }

        }

        return true;
    }
//validates input of cab type
    bool Parser::validateCab(string s) {
        int cabId, taxiType;
        char  manufacturer, color;
    //empty whitespace in begining of string
    boost::algorithm::trim_left(s);
        vector<string> strs;
        boost::split(strs, s, boost::is_any_of(","));
        //if there are incompatible number of inputs
        if (strs.size() != 4) {
            return false;
        }
        for (int i = 0; i < 2; ++i) {
                //if one of the numbers is not integer or negative
                if (!checkNumber(strs[i])) {
                    return false;
            }

        }
        //if it's non-included cab type
        if (strs[1].compare("2") != 0 && strs[1].compare("1") != 0){
            return false;
        }
            //if it's non-included manufacturer
        if (strs[2].compare("H") != 0 && strs[2].compare("S") != 0 && strs[2].compare("T") != 0 &&
            strs[2].compare("F") != 0) {
            return false;
        }
        //if it's non-included color
        if (strs[3].compare("R") != 0 && strs[3].compare("B") != 0 && strs[3].compare("G") != 0 &&
            strs[3].compare("P") != 0 &&strs[3].compare("W") != 0  ) {
            return false;
        }
    //cast string to type needed
    cabId = boost::lexical_cast<int>(strs[0]);
        taxiType = boost::lexical_cast<int>(strs[1]);
        manufacturer = boost::lexical_cast<char>(strs[2]);
        color = boost::lexical_cast<char>(strs[3]);
    //insert to taxicenter
    this->taxi->buyCab(cabId,taxiType,manufacturer,color);
        return true;
    }
bool Parser:: checkObsticale(string s,int maxX,int maxY){
    int xObstacle, yObstacle;
    boost::algorithm::trim_left(s);
    vector<string> strs;
    boost::split(strs, s, boost::is_any_of(","));
    //if there are incompatible number of inputs
    if (strs.size() != 2) {
        return false;
    }
    for (int i = 0; i <strs.size() ; ++i) {
        //if one of the numbers is not integer or negative
        if (!checkNumber(strs[i])) {
            return false;
        }
    }
    //cast string to type needed
    xObstacle = boost::lexical_cast<int>(strs[0]);
    yObstacle= boost::lexical_cast<int>(strs[1]);
    if(xObstacle>maxX || yObstacle>maxY){
        return false;
    }
    //enters all the points from the user as obstacles
    this->taxi->getMap()->addObstacles(Point (xObstacle, yObstacle));
    return true;
}
bool Parser::validateMap(string s) {
    int xGrid, yGrid, numOfObstacles;

    boost::algorithm::trim_left(s);
    vector<string> strs;
    boost::split(strs, s, boost::is_any_of(" "));
    //if there are incompatible number of inputs
    if (strs.size() != 2) {
        return false;
    }
    for (int i = 0; i <strs.size() ; ++i) {
        //if one of the numbers is not integer or negative
        if (!checkNumber(strs[i])) {
            return false;
        }
    }
    //cast string to type needed
    xGrid = boost::lexical_cast<int>(strs[0]);
    yGrid = boost::lexical_cast<int>(strs[1]);
    Map* m = new Map(xGrid,yGrid);
    //create the map according to the size entered by the
    this->taxi->setMap(m);
    getline(cin,s);
    boost::algorithm::trim_left(s);
    if(!checkNumber(s)){
        return false;
    }
    numOfObstacles = boost::lexical_cast<int>(s);
    for (int i = 0; i < numOfObstacles; ++i) {
        getline(cin,s);
        if(!checkObsticale(s,xGrid,yGrid)){
            return false;
        }
    }
    return true;
}


