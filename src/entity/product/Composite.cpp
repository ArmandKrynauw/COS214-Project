#include "Composite.h"

Composite::Composite(std::string name, std::string type) : Entity(name, type) { }

Composite::~Composite() {}

void Composite::add(Entity* entity) { }

void Composite::remove(int a) { }

int Composite::getDamage() const { }

Entity* Composite::clone() { }

void Composite::update(){
    int damage = 0;
    for (int i = 0; i < units.size(); i++)
    {
        damage+= units.at(i)->getDamage();
    }
    // this->setDamage(damage);
}
