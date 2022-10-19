#include "SeaUnitFactory.h"
#include "../product/SeaUnitLight.h"
#include "../product/SeaUnitMedium.h"
#include "../product/SeaUnitHeavy.h"

SeaUnitFactory::SeaUnitFactory() {
    type = "sea";
}

Unit *SeaUnitFactory::createLightUnit(std::string name) {
    return new SeaUnitLight(name, type, 50, 5);
}

Unit *SeaUnitFactory::createMediumUnit(std::string name) {
    return new SeaUnitMedium(name, type, 75, 10);
}

Unit *SeaUnitFactory::createHeavyUnit(std::string name) {
    return new SeaUnitHeavy(name, type, 100, 20);
}

SeaUnitFactory::~SeaUnitFactory() { }
