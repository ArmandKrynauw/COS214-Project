#ifndef CARETAKER_H
#define CARETAKER_H

#include "Memento.h"
#include <vector>

class CareTaker {
private:
    std::vector<Memento *> states;

public:
    CareTaker();

    void store(Memento *state);

    Memento *undo();

    void clear();

    ~CareTaker();
};

#endif