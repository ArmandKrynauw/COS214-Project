#ifndef DEADSTATE_H
#define DEADSTATE_H

#include "UnitState.h"

class DeadState : public UnitState {
    public:
        virtual void handleChange(Unit* u);
        virtual std::string getState();
};
#endif // DEADSTATE_H