#ifndef MEMENTO_H
#define MEMENTO_H

#include "State.h"
class Memento  {
    private:
        State *state;
    public:
        Memento(State* state);
        void setState(State * state);
        State * getState();
        void clear();
        ~Memento();
};

#endif