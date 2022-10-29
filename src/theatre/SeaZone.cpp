#include "SeaZone.h"
#include "../entity/product/Entity.h"

SeaZone::SeaZone(std::string name) : Zone(name) {
    this->name +=  "_SeaZone";
}

std::string SeaZone::getType(){
    return "sea";
}

int SeaZone::getDamageDivisor() {
    // Ships tend to have very low engagement rates, while having much higher decisive battles
    int capacity = getUnitCount();

    if(capacity > 2){
        return capacity / 2;
    }
    
    return capacity;
}

SeaZone::~SeaZone() {}
