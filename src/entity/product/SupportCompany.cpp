#include "SupportCompany.h"

SupportCompany::SupportCompany(Entity *entity) : Entity() {
    this->entity = entity;
}

int SupportCompany::getDamage() { entity->getDamage(); }

int SupportCompany::getHP() {
    return entity->getHP();
}

int SupportCompany::getValue() const {
    return entity->getValue();
}

bool SupportCompany::takeDamage(int damage) {
    return entity->takeDamage(damage);
}

int SupportCompany::getUnitCount() const {
    return entity->getUnitCount();
}

void SupportCompany::print() {
    entity->print();
}

void SupportCompany::setTheatre(Theatre *theatre) {
    entity->setTheatre(theatre);
}

Entity *SupportCompany::clone() {
    return entity->clone();
}

nlohmann::json SupportCompany::toJSON() const {
    return entity->toJSON();
}

SupportCompany::~SupportCompany() {
    delete entity;
}

