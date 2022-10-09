#ifndef LANDUNITHEAVY_H
#define LANDUNITHEAVY_H

#include "LandUnit.h"

class LandUnitHeavy : public LandUnit{
    private:
        int HP = 100;
        int damage = 20;

    public:
        LandUnitHeavy();
        ~LandUnitHeavy();
};
#endif