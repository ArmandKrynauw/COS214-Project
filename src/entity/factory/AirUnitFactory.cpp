#include "AirUnitFactory.h"
#include "../product/AirUnitLight.h"
#include "../product/AirUnitMedium.h"
#include "../product/AirUnitHeavy.h"

AirUnitFactory::AirUnitFactory() {
    type = "air";
}

Unit *AirUnitFactory::createLightUnit(std::string name) {
    return new AirUnitLight(name, type, 50, 5);
}

Unit *AirUnitFactory::createMediumUnit(std::string name) {
    return new AirUnitMedium(name, type, 75, 10);
}

Unit *AirUnitFactory::createHeavyUnit(std::string name) {
    return new AirUnitHeavy(name, type, 100, 20);
}

AirUnitFactory::~AirUnitFactory() { }
