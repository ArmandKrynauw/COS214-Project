#include "LandUnitFactory.h"

#include "../product/LandUnitHeavy.h"
#include "../product/LandUnitLight.h"
#include "../product/LandUnitMedium.h"

LandUnitFactory::LandUnitFactory() {
    
    type = "land";
}

Unit *LandUnitFactory::createLightUnit(std::string name) {
    return new LandUnitLight(name, type, 50, 5, 30);
}

Unit *LandUnitFactory::createMediumUnit(std::string name) {
    return new LandUnitMedium(name, type, 75, 10, 40);
}

Unit *LandUnitFactory::createHeavyUnit(std::string name) {
    return new LandUnitHeavy(name, type, 100, 20, 50);
}

LandUnitFactory::~LandUnitFactory() {}