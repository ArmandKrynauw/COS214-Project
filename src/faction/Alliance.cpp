#include "Alliance.h"
#include "Faction.h"

Alliance::Alliance(std::string name) : Faction(name) { name = name; }

void Alliance::addCountry(Country* country) { members.push_back(country); }

void Alliance::removeCountry(Country* country) {
    int counter = 0;
    for (Faction* p : members) {

        if (p->getName() == country->getName()) {

            members.erase(members.begin() + counter);
            break;
        }
        counter++;
    }
}

int Alliance::getResourceCount() {
    int baseResourceCount = 0;
    for (Faction* p : members) {
        baseResourceCount += p->getResourceCount();
    }
    return baseResourceCount;
}

void Alliance::setResourceCount(int baseResourceCount) {
    this->baseResourceCount = baseResourceCount;
}

Alliance* Alliance::getAlliance() { return this; }

void Alliance::makeDecision() {
    for (Faction* p : members) {

        p->makeDecision();
    }
} // For each member in alliance call makeDecision()

void Alliance::chooseStrategy() {
    for (Faction* p : members) {

        p->chooseStrategy();
    }
}