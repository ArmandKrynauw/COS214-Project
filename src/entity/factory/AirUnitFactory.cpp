#include "AirUnitFactory.h"

#include "../product/AirUnitHeavy.h"
#include "../product/AirUnitLight.h"
#include "../product/AirUnitMedium.h"

AirUnitFactory::AirUnitFactory() {
    type = "air";
}

Unit *AirUnitFactory::createLightUnit(std::string name) {
    return new AirUnitLight(name, type, 50, 5, 30);
}

Unit *AirUnitFactory::createMediumUnit(std::string name) {
    return new AirUnitMedium(name, type, 75, 10, 40);
}

Unit *AirUnitFactory::createHeavyUnit(std::string name) {
    return new AirUnitHeavy(name, type, 100, 20, 50);
}

AirUnitFactory::~AirUnitFactory() {}
