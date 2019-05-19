

/*this class is the most basic object.
 * it holds an x axis and a y axis because it represents a 2 dimensional world.
  */
#include "Point.h"

//operator overloading so we can compare two objects
bool Point::operator==(const Point &p1) const {
    return ((x == p1.x) && (y == p1.y));
}

//operator overloading so we can print a point using <<
ostream &operator<<(ostream &os, const Point &point) {
    return os << "(" << point.x << "," << point.y << ")" << endl;


}

//x is private so we have a function to get x
int Point:: getX()const {
    return x;
}

//y is private so we have a function to get y
int Point::getY()const {
    return y;
}
//destructor is not used because we don't allocate any memory we need to free
Point::~Point() {
}