#ifndef INJUREDSTATE_H
#define INJUREDSTATE_H
#include "UnitState.h"

class InjuredState : public UnitState {
    public:
        virtual void handleChange(Unit* u);
        virtual std::string getState();
};
#endif
