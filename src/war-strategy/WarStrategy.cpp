#include "WarStrategy.h"

WarStrategy::WarStrategy(){
    this->planned = false;
}

void WarStrategy::setPlanned(bool b){
    this->planned = b;
}

bool WarStrategy::getPlanned(){
    return this->planned;
}

std::string WarStrategy::getDefendant() const {
    return defendant; 
}

WarStrategy::~WarStrategy() { }