#include "Theatre.h"

Theatre::Theatre(std::string name, bool seaZone) {
    this->name = name;
    this->id = uuid::generate();
    if(seaZone) this->limit = 3;
    else
    this->limit = 2;
}

Theatre::~Theatre() { }

void Theatre::addFaction(std::string faction) {
    if (armies.count(faction)) {
        return;
    }

    std::vector<Zone*> army;
    army.push_back(landFactory->createZone(name));
    army.push_back(airFactory->createZone(name));
    if(limit==3){ army.push_back(seaFactory->createZone(name)); }

    armies[faction] = army;
}

void Theatre::removeFaction(std::string faction) {
    if (armies.count(faction)) {
        std::vector<Zone*> zones = armies[faction];
        for (int i = 0; i < zones.size(); i++) {
            delete zones[i];
        }
    }
}

std::string Theatre::getName() const {
    return name;
}

void Theatre::addUnit(std::string faction, Unit* unit) {
    if (!armies.count(faction)) {
        addFaction(faction);
    }

    std::vector<Zone*> zones = armies[faction];

    for (int i = 0; i < zones.size(); i++) {
         if (zones[i]->getType() == unit->getType()){
             zones[i]->addUnit(unit);
             break;
         } 
    }
}

Unit* Theatre::removeUnit(std::string faction, std::string type, int index) {
    if (!armies.count(faction)) {
        throw WarException("Faction not found.");
    }
    
    Unit* unit = NULL;
    std::vector<Zone*> zones = armies[faction];

    for (int i = 0; i < zones.size(); i++) {
         if (zones[i]->getType() == type) {
            if (index < 0 || index >= zones.size()) {
                throw WarException("Unit not found.", "out-of-bounds");
            }
             unit = zones[i]->removeUnit(index);
             break;
         } 
    }

    if (!unit) {
        throw WarException("Unit not found.");
    }

    return  unit;
}

void Theatre::Battle(std::string attackingFaction,std::string defendingFaction) {
    // auto it = factions.find(attacker);
    // int indexAttacker = it->second;

    // it = factions.find(defender);
    // int indexDefender = it->second;

    int attackModifier = strategies[attackingFaction]->executeStrategy(strategies[defendingFaction]);

    int defendModifier = strategies[defendingFaction]->executeStrategy(strategies[attackingFaction]);

    // int attackModifier = strategies.at(indexAttacker)->executeStrategy(strategies.at(indexDefender));
    // int defendModifier = strategies.at(indexDefender)->executeStrategy(strategies.at(indexAttacker));

    int attackFinal;
    int defendFinal;

    for(int i = 0 ; i < limit; i++)
    {
        attackFinal = armies[attackingFaction][i]->sum()*attackModifier;
        defendFinal = armies[defendingFaction][i]->sum()*defendModifier;

        armies[attackingFaction][i]->takeDamage(defendFinal);  // defender deals damage
        armies[defendingFaction][i]->takeDamage(attackFinal);  // attacker deals damage
    }

    //would probably want to display results here
    return;

}

void Theatre::changeStrategy(std::string faction, WarStrategy* strategy) {
    if (!strategy) {
        throw WarException("NULL Strategy");
    }

    if (dynamic_cast<AttackStrategy*>(strategy)) {
        if(strategies[faction]->getPlanned()) {
            strategy->setPlanned(true);
        }
    }
    strategies[faction] = strategy;
}
