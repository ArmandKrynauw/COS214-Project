#include "Memento.h"

Memento::Memento(State* state) {
    State * newState = new State();
    newState = state;
    this->state = newState;
}

void Memento::setState(State * state) {
    this->state = state;
}

State * Memento::getState() {
    return this->state;
}

void Memento::clear() {
    delete this->state;
}

Memento::~Memento() {
    delete this->state;
}