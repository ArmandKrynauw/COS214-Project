#include "AirZone.h"

AirZone::AirZone(std::string name, std::string type) : Zone(name, this->type) {}

AirZone::~AirZone() {}