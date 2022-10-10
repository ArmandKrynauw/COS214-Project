#include "Theatre.h"

Theatre::Theatre(std::string name) {
    this->name = name;
    this->id = uuid::generate();
}

void Theatre::addFaction(Faction* faction) {
    if (!faction) {
        // throw WarException("Null pointer exception", "invalid-pointer");
    }
    factions.push_back(faction);
}

void Theatre::removeFaction(Faction* faction) {
    for (int i = 0; i < factions.size(); i++) {
        if (factions[i]->equals(faction)) {
            factions.erase(factions.begin() + i);
        }
    }
}

void Theatre::battle() {
    // std::pair<int, int>(factions.first->getDamage(),
    // factions.second->getDamage()) attackPower;
    // factions.first->takeDamage(attackPower.second);

    // factions.second->takeDamage(attackPower.first);
    // factions.first()->takeDamage(factions.second()->getDamage());

    // int* attackPowers = new int[factions.size()];

    std::unordered_map<std::string, int> attackPowers;
    for (int i = 0; i < factions.size(); i++) {
        attackPowers[factions[i]->getId()] = factions[i]->getAttackPower(this);
    }

    for (int i = 0; i < factions.size(); i++) {
        for (int j = 0; j < factions.size(); j++) {

		}
    }

    // F1: Defend
    // F2: Attack

    // F1: HP Boost +10%
    // F2: Power Boost +10%
}

void Theatre::setFactionStrategy(Faction* faction, Strategy* strategy) {
    strategies[faction->getId()] = strategy;
    // 3 strategies
    // Create Strategy in War Engine
}

Theatre::~Theatre() {}