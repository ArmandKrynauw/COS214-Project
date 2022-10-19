#ifndef UNITSTATE_H
#define UNITSTATE_H
#include <iostream>

class Unit;

class UnitState {
    public:
        virtual void handleChange(Unit* u) = 0;
        virtual std::string getState() = 0;
};
#endif
