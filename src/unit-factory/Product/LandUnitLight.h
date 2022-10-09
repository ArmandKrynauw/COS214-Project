#ifndef LANDUNITLIGHT_H
#define LANDUNITLIGHT_H

#include "LandUnit.h"

class LandUnitLight : public LandUnit{
    private:
        int HP = 50;
        int damage = 5;

    public:
        LandUnitLight();
        ~LandUnitLight();
};
#endif