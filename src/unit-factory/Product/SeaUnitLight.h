#define SEAUNITLIGHT_H
#ifndef SEAUNITLIGHT_H

#include "SeaUnit.h"

class SeaUnitLight : public SeaUnit{
    private:
        int HP = 50;
        int damage = 5;

    public:
        SeaUnitLight();
        ~SeaUnitLight();
};
#endif
