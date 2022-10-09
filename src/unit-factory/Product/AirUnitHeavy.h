#ifndef AIRUNITHEAVY_H
#define AIRUNITHEAVY_H

#include "AirUnit.h"

class AirUnitHeavy : public AirUnit{
    private:
        int HP = 100;
        int damage = 20;

    public:
        AirUnitHeavy();
        ~AirUnitHeavy();
};

#endif // AIRUNITHEAVY_H