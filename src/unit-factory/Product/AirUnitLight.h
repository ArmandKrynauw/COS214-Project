#ifndef AIRUNITLIGHT_H
#define AIRUNITLIGHT_H

#include "AirUnit.h"

class AirUnitLight : public AirUnit{
    private:
        int HP = 50;
        int damage = 5;

    public:
        AirUnitLight();
        ~AirUnitLight();
};
#endif // AIRUNITLIGHT_H