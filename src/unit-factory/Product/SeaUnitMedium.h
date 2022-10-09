#ifndef SEAUNITMEDIUM_H
#define SEAUNITMEDIUM_H

#include "SeaUnit.h"

class SeaUnitMedium : public SeaUnit{
    private:
        int HP = 75;
        int damage = 10;

    public:
        SeaUnitMedium();
        ~SeaUnitMedium();
};
#endif
