#include "WarStrategy.h"

WarStrategy::WarStrategy(std::string target) : target(target) {
    this->planned = false;
}

void WarStrategy::setPlanned(bool b) {
    this->planned = b;
}

bool WarStrategy::getPlanned() {
    return this->planned;
}

std::string WarStrategy::getTarget() const {
    return target;
}

std::string WarStrategy::getType() {
    return type;
}

WarStrategy::~WarStrategy() {}