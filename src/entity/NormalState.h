#pragma once
#include "UnitState.h"

class NormalState : public UnitState {
    public:
        virtual void handleChange(Unit* u);
        virtual std::string getState();
};
