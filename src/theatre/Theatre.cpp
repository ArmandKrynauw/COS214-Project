#include "Theatre.h"

Theatre::Theatre(std::string name, bool seaZone) {
    this->name = name;
    this->id = uuid::generate();
    if(seaZone) this->limit = 3;
    else
    this->limit = 2;
    landFactory = new LandZoneFactory();
    seaFactory = new SeaZoneFactory();
    airFactory = new AirZoneFactory();
}

Theatre::~Theatre() { }

void Theatre::addFaction(std::string faction) {
    if (zones.count(faction)) {
        return;
    }
    
    std::vector<Zone*> armedForce;
    armedForce.push_back(landFactory->createZone(this->name)); //seg fault
    
    armedForce.push_back(airFactory->createZone(name));
    if(limit==3){ armedForce.push_back(seaFactory->createZone(name)); }
    
    zones[faction] = armedForce;
    strategies[faction] = NULL;
}

void Theatre::removeFaction(std::string faction) {
    if (zones.count(faction)) {
        std::vector<Zone*> factionZones = zones[faction];
        for (int i = 0; i < factionZones.size(); i++) {
            delete factionZones[i];
        }
    }
}

std::string Theatre::getName() const {
    return name;
}

std::string Theatre::getId() const {
    return id;
}

void Theatre::addUnit(std::string faction, Unit* unit) {
    if (!zones.count(faction)) {
        addFaction(faction);
    }

    
    
    std::vector<Zone*> factionZones = zones[faction];

    for (int i = 0; i < factionZones.size(); i++) {
         if (factionZones[i]->getType() == unit->getType()){
             factionZones[i]->addUnit(unit);
             break;
         } 
    }
}

Unit* Theatre::removeUnit(std::string faction, std::string type, int index) {
    if (!zones.count(faction)) {
        throw WarException("Faction not found.");
    }
    
    Unit* unit = NULL;
    std::vector<Zone*> factionZones = zones[faction];

    for (int i = 0; i < factionZones.size(); i++) {
         if (factionZones[i]->getType() == type) {
            if (index < 0 || index >= factionZones.size()) {
                throw WarException("Unit not found.", "out-of-bounds");
            }
             unit = factionZones[i]->removeUnit(index);
             break;
         } 
    }

    if (!unit) {
        throw WarException("Unit not found.");
    }

    // TODO: Check if Faction has any Units left in the Theatre
    // after a Unit has been removed. If it doesn't then remove the Faction
    // and its zones from the Theatre.

    // bool removeFaction = true;
    // for (int i = 0; i < factionZones.size(); i++) {
    //     if (factionZones[i]-size() > 0) {

    //     }
    // }

    return  unit;
}

void Theatre::battle() {
    // auto it = factions.find(attacker);
    // int indexAttacker = it->second;

    // it = factions.find(defender);
    // int indexDefender = it->second;

    // int attackModifier = strategies[attackingFaction]->executeStrategy(strategies[defendingFaction]);
    // int defendModifier = strategies[defendingFaction]->executeStrategy(strategies[attackingFaction]);

    // // int attackModifier = strategies.at(indexAttacker)->executeStrategy(strategies.at(indexDefender));
    // // int defendModifier = strategies.at(indexDefender)->executeStrategy(strategies.at(indexAttacker));

    // int attackFinal;
    // int defendFinal;

    // for(int i = 0 ; i < limit; i++)
    // {
    //     attackFinal = armies[attackingFaction][i]->sum()*attackModifier;
    //     defendFinal = armies[defendingFaction][i]->sum()*defendModifier;

    //     armies[attackingFaction][i]->takeDamage(defendFinal);  // defender deals damage
    //     armies[defendingFaction][i]->takeDamage(attackFinal);  // attacker deals damage
    // }

    std::unordered_map<std::string, WarStrategy*>::iterator it = strategies.begin();
    if(strategies.size() > 1){
        std::cout<<getName()<<" has a battle."<<std::endl;
        while (it != strategies.end()) {
            std::string attacker = it->first;
            std::string defendant = it->second->getTarget();
            WarStrategy* strategy = it->second;
            float attackModifier = strategy->executeStrategy(strategies[defendant]);
            float defendModifier = strategies[defendant]->executeStrategy(strategies[attacker]);
            
            for(int i = 0 ; i < limit; i++) {
                if(zones[attacker][i]->getUnitCount() > 0 && zones[defendant][i]->getUnitCount() > 0){
                    int attackFinal = zones[attacker][i]->getTotalDamage() * attackModifier;
                    int defendFinal = zones[defendant][i]->getTotalDamage() * defendModifier;
                    
                    zones[attacker][i]->takeDamage(defendFinal);  // defender deals damage
                    
                    //zones[defendant][i]->takeDamage(attackFinal);  // attacker deals damage
                }
            }
            it++;
        }
    }
    else if(strategies.size() == 1){
        //When Only one faction has a strategy
    }
    else {
        //Nobody in Theatre
        std::cout<<getName()<<" is neutral."<<std::endl;
    }

   //results?
    return;

}

void Theatre::changeStrategy(std::string faction, WarStrategy* strategy) {
   
    if (!strategy) {
        throw WarException("NULL Strategy");
    }

    if (strategy->getType() == "Attack") {
        if(strategies[faction] != NULL && strategies[faction]->getPlanned()) {
            strategy->setPlanned(true);
        }
    }
    strategies[faction] = strategy;
}

void Theatre::printTheatre(){
     std::unordered_map<std::string, std::vector<Zone*>>::iterator it = zones.begin();
    std::cout<<getName()<<": "<<std::endl;
    while(it != zones.end()){
        std::cout<<"\t"<<it->first<<": "<<std::endl;
        for(Zone * z : it->second){
            std::cout<<"\t\t"<<z->getName()<<"["<<z->getTotalDamage()<<"]"<<std::endl;
            // int sum = 0;
            // for(Unit* u: z->getUnits()){
            //     sum+=u->getHP();
            // }
            // std::cout<<sum<<std::endl;
        }
        
        it++;
    }
}

bool Theatre::checkForFaction(std::string factionName){
    std::unordered_map<std::string, std::vector<Zone*>>::iterator it = zones.begin();
    while(it != zones.end()){
        if(it->first == factionName){ return true; }
        it++;
    }
    return false;
}

void Theatre::printStrategies(){
    std::cout<<getName()<<": "<<std::endl;
    if(strategies.size() != 0){
       std::unordered_map<std::string, WarStrategy*>::iterator it = strategies.begin();

       while(it != strategies.end()){
            std::cout<<"\t"<<it->first<<": "<<it->second->getType()<<std::endl;
            it++;
       }
       
    } else{
        std::cout<<getName()<<" is Empty."<<std::endl;
    }
    //std::cout<<std::endl;
}
