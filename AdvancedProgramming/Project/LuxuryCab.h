#include "Cab.h"
#include <boost/serialization/export.hpp>
/**
* class luxurycab. responsible for the moving on the map. inherits from cab
        * moves two steps every time unless there is only 1 step left.
*/
#ifndef MISSION2_LUXURYCAB_H
#define MISSION2_LUXURYCAB_H


class LuxuryCab: public Cab {

private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Cab>(*this);
    }

public:

    //constructor
    LuxuryCab(int cabId, char manufacturer, char color, PointNode* location);

    LuxuryCab(){}

    //destructor
    ~LuxuryCab();

    //moves the cab along the map
    PointNode * move(vector<PointNode *> v, PointNode * n);
};


#endif //MISSION2_LUXURYCAB_H
