/**
* class cab. responsible for the moving on the map. this kind of cab
* moves only one step every time on the map.
*/
#include "Cab.h"

//constructor
// gets char ang assigns an enum that is equivalent to the caller of the ctor's choice.
Cab::Cab(int cabId, char manufacturer, char color, PointNode* location):cabId(cabId), location(location){
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
PointNode * Cab::move(vector<PointNode *> v, PointNode * n){
    for (int i = 0; i < v.size()-1; ++i) {
        if (v[i] == n) {
            this->location = v[i+1];
            return this->location;
        }
    }
    return this->location;
}

//gets the cab's id
int Cab::getCabId() const {
    return cabId;
}

//gets the location of the cab
PointNode * Cab::getLocation() const {
    return location;
}

//sets the location of the cab
void Cab::setLocation(PointNode * location) {
    Cab::location = location;
}

//set the course to the current trip
void Cab::setCurrentWay(const vector<PointNode *> &currentWay) {
    this->currentWay = currentWay;
}

//destructor
Cab::~Cab() {
}
//default constructor
Cab::Cab() {

}

const vector<PointNode *> &Cab::getCurrentWay() const {
    return currentWay;
}

bool Cab::isInDrive() const {
    return inDrive;
}

void Cab::setInDrive(bool inDrive) {
    Cab::inDrive = inDrive;
}

BOOST_CLASS_EXPORT(Cab)

