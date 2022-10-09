#pragma once
#include <iostream>

#include "../unit-factory/Product/LandUnit.h"

class UnitState {
    public:
        virtual void handleChange(Unit* u) = 0;
        virtual std::string getState() = 0;
};