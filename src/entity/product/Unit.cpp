#include "Unit.h"

using json = nlohmann::json;

Unit::Unit() {}

Unit::Unit(const Unit& unit) : Entity(unit) {
    this->damage = unit.damage;
    this->HP = unit.HP;
    this->initialHP = unit.initialHP;
    this->value = unit.value;
	this->theatre = unit.theatre;
}

Unit::Unit(std::string name, std::string type, int HP, int damage, int value)
        : Entity(name, type), HP(HP), damage(damage), value(value), theatre(NULL) ,initialHP(HP) {}

int Unit::getHP() const {
    return HP;
}

int Unit::getInitialHP() const {
    return initialHP;
}

int Unit::getDamage() const {
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

void Unit::setTheatre(Theatre *theatre) {
    this->theatre = theatre;
}

void Unit::clearCasualties() {}

json Unit::toJSON() const {
    return json{
            {"name",    name},
            {"type",    type},
            {"initialHP", initialHP},
            {"currentHP", HP},
            {"damage",  damage},
            {"theatre", (theatre) ? theatre->getName() : "Evacuated"},
            {"id", id}
    };
}

Theatre *Unit::getTheatre() {
    return theatre;
}

Unit::~Unit() {}