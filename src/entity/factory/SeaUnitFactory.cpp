#include "SeaUnitFactory.h"

#include "../product/SeaUnitHeavy.h"
#include "../product/SeaUnitLight.h"
#include "../product/SeaUnitMedium.h"

SeaUnitFactory::SeaUnitFactory() {
    type = "sea";
}

Unit* SeaUnitFactory::createLightUnit(std::string name) {
    return new SeaUnitLight(name, type, 50, 5, 30);
}

Unit* SeaUnitFactory::createMediumUnit(std::string name) {
    return new SeaUnitMedium(name, type, 75, 10, 40);
}

Unit* SeaUnitFactory::createHeavyUnit(std::string name) {
    return new SeaUnitHeavy(name, type, 100, 20, 50);
}

SeaUnitFactory::~SeaUnitFactory() {}
