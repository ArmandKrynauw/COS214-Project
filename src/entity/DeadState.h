#pragma once
#include "UnitState.h"

class DeadState : public UnitState {
    public:
        virtual void handleChange(Unit* u);
        virtual std::string getState();
};