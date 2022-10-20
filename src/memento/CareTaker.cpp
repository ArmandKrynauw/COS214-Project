#include "CareTaker.h"

CareTaker::CareTaker() {
    this->states = std::vector<Memento *>();
}

void CareTaker::store(Memento *state) {
    this->states.push_back(state);
}

Memento * CareTaker::undo() {
    Memento * state = this->states.back();
    this->states.pop_back();
    return state;
}

void CareTaker::clear() {
    for (int i = 0; i < this->states.size(); i++) {
        this->states[i]->clear();
    }
    this->states.clear();
}

CareTaker::~CareTaker() {
    this->clear();
}