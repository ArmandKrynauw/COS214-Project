#ifndef AIRUNITMEDIUM_H
#define AIRUNITMDEIUM_H

#include "AirUnit.h"

class AirUnitMedium : public AirUnit{
    private:
        int HP = 75;
        int damage = 10;

    public:
        AirUnitMedium();
        ~AirUnitMedium();
};
#endif