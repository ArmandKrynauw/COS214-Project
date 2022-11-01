#include "Unit.h"

using json = nlohmann::json;

Unit::Unit(std::string name, std::string type, int HP, int damage, int value)
        : Entity(name, type), HP(HP), damage(damage), value(value), theatre(NULL) {}

int Unit::getHP() {
    return HP;
}

int Unit::getDamage() {
    return damage;
}

int Unit::getValue() const {
    return value;
}

void Unit::setHP(int HP) {
    this->HP = HP;
}

void Unit::setDamage(int damage) {
    this->damage = damage;
}

bool Unit::takeDamage(int damage) {
    HP = (HP - damage <= 0) ? 0 : HP - damage;
    return HP == 0;
}

int Unit::getUnitCount() const {
    return 1;
}

void Unit::print() {
    std::cout << this->name + " HP: " + std::to_string(this->HP) +
                 " Damage: " + std::to_string(this->damage)
              << std::endl;
}

void Unit::setTheatre(Theatre *theatre) {
    this->theatre = theatre;
}

json Unit::toJSON() const {
    return json{
            {"name",    name},
            {"type",    type},
            {"hp",      HP},
            {"damage",  damage},
            {"theatre", (theatre) ? theatre->getName() : "None"}
    };
}

std::string Unit::getName() const {
    return name;
}

Theatre *Unit::getTheatre() {
    return theatre;
}

Unit::~Unit() {}