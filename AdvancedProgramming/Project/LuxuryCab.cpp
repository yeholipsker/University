/**
* class luxurycab. responsible for the moving on the map. inherits from cab
        * moves two steps every time unless there is only 1 step left.
*/

#include "LuxuryCab.h"

//constructor
LuxuryCab::LuxuryCab(int cabId, char manufacturer, char color, PointNode* location){

    this->location=location;
    this->cabId=cabId;
    switch (manufacturer) {
        case 'H':
            this->manufacturer = HONDA;
            break;
        case 'S':
            this->manufacturer = SUBARO;
            break;
        case 'T':
            this->manufacturer = TESLA;
            break;
        case 'F':
            this->manufacturer = FIAT;
            break;
    }

    switch (color) {
        case 'R':
            this->color = RED;
            break;
        case 'B':
            this->color = BLUE;
            break;
        case 'G':
            this->color = GREEN;
            break;
        case 'P':
            this->color = PINK;
            break;
        case 'W':
            this->color = WHITE;
            break;
    }
    this->setInDrive(false);
}

//moves the cab along the map
PointNode * LuxuryCab::move(vector<PointNode *> v, PointNode * n) {
    PointNode * temp = Cab::move(v, n);
    if (v[v.size()-1] != temp) {
        temp = Cab::move(v,temp);
    }
    return temp;
}

//destructor
LuxuryCab::~LuxuryCab() {
}


BOOST_CLASS_EXPORT(LuxuryCab)