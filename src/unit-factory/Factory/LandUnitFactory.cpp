#include "LandUnitFactory.h"

#include "../Product/LandUnitLight.h"
#include "../Product/LandUnitMedium.h"
#include "../Product/LandUnitHeavy.h"

LandUnitFactory::LandUnitFactory() {
    // typeOfUnit = "Land";
}

Unit *LandUnitFactory::createLightUnit(std::string name) {
    //pass name as a parameter to LandUnitLight constructor?
    return new LandUnitLight();
}

Unit *LandUnitFactory::createMediumUnit(std::string name) {
    // pass name as a parameter to LandUnitMedium constructor?
    return new LandUnitMedium();
}

Unit *LandUnitFactory::createHeavyUnit(std::string name) {
    // pass name as a parameter to LandUnitHeavy constructor?
    return new LandUnitHeavy();
}

LandUnitFactory::~LandUnitFactory() {
}