#ifndef UNITSTATE_H
#define UNITSTATE_H

#include <iostream>
#include "../unit-factory/Product/LandUnit.h"

class UnitState {
    public:
        virtual void handleChange(Unit* u) = 0;
        virtual std::string getState() = 0;
};
#endif // UNITSTATE_H