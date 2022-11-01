#include "Engineers.h"

Engineers::Engineers(Entity *entity) : SupportCompany(entity) {

}

int Engineers::getDamage() {
    return SupportCompany::getDamage() * 1.25;
}

int Engineers::getHP() {
    return SupportCompany::getHP();
}

Engineers::~Engineers() {

}