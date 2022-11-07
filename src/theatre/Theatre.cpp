#include "Theatre.h"
#include "../entity/product/Entity.h"

Theatre::Theatre(std::string name, bool seaZone, int resource) {
    this->name = name;
    this->id = uuid::generate();
    if (seaZone) this->limit = 3;
    else
        this->limit = 2;
    landFactory = new LandZoneFactory();
    seaFactory = new SeaZoneFactory();
    airFactory = new AirZoneFactory();
    this->resource = resource;
}

Theatre::~Theatre() {}

void Theatre::addFaction(std::string faction) {
    if (zones.count(faction)) {
        return;
    }

    std::vector<Zone *> armedForce;
    armedForce.push_back(landFactory->createZone(this->name)); //seg fault

    armedForce.push_back(airFactory->createZone(name));
    if (limit == 3) { armedForce.push_back(seaFactory->createZone(name)); }

    zones[faction] = armedForce;
    strategies[faction] = NULL;
}

void Theatre::removeFaction(std::string faction) {
    if (zones.count(faction)) {
        std::vector<Zone *> factionZones = zones[faction];
        for (int i = 0; i < factionZones.size(); i++) {
            delete factionZones[i];
        }
    }
}

std::string Theatre::getName() {
    return name;
}

std::string Theatre::getId() const {
    return id;
}

void Theatre::addEntity(std::string faction, Entity *entity) {
    //std::cout<<entity->getName()<<std::endl;
    if (!entity) {
        return;
    }
    if (!zones.count(faction)) {
        addFaction(faction);
    }

    float num = checkOpposition(faction);

    entity->takeDamage(entity->getHP()*0.1*num);

    std::vector<Zone *> factionZones = zones[faction];

    for (int i = 0; i < factionZones.size(); i++) {
        if (factionZones[i]->getType() == entity->getType()) {
            entity->setTheatre(this);
            factionZones[i]->addEntity(entity);
            break;
        }
    }
}

Entity *Theatre::removeEntity(std::string faction, std::string type, std::string id) {
    
    if (!zones.count(faction)) {
        throw WarException("Faction not found.");
    }

    Entity *entity = NULL;
    std::vector<Zone *> factionZones = zones[faction];
    for (int i = 0; i < factionZones.size(); i++) {
        if (factionZones[i]->getType() == type) {
            entity = factionZones[i]->removeEntity(id);
            break;
        }
    }
    if (!entity) {
        throw WarException("Entity not found.");
    }

    entity->setTheatre(NULL);
    return entity;
}

void Theatre::battle() {
    std::unordered_map<std::string, WarStrategy *>::iterator it = strategies.begin();
    if (strategies.size() > 1) {
        while (it != strategies.end()) {
            if(it->second && strategies[it->second->getTarget()]){
                std::string attacker = it->first;                   
                std::string defendant = it->second->getTarget();    
                WarStrategy *strategy = it->second;
                float attackModifier = 1;
                float defendModifier = 1;
                
                if(strategy){
                    attackModifier = strategy->executeStrategy(strategies[defendant]);
                }
                if(strategies[defendant]){
                    defendModifier = strategies[defendant]->executeStrategy(strategies[attacker]);
                } 

                for (int i = 0; i < limit; i++) {
                    if (zones[attacker][i]->getUnitCount() > 0 && zones[defendant][i]->getUnitCount() > 0) {
                        int attackFinal = zones[attacker][i]->getTotalDamage() * attackModifier;
                        int defendFinal = zones[defendant][i]->getTotalDamage() * defendModifier;
                        zones[attacker][i]->takeDamage(defendFinal);   
                    }
                }
            }
            it++;
        }
    } 
    return;

}

void Theatre::changeStrategy(std::string faction, WarStrategy *strategy) {

    if (!strategy) {
        throw WarException("NULL Strategy");
    }

    if (strategy->getType() == "Attack") {
        if (strategies[faction] != NULL && strategies[faction]->getType() == "Plan") {
            strategy->setPlanned(true);
        }
    }
    strategies[faction] = strategy;
}

void Theatre::printTheatre() {
    std::unordered_map<std::string, std::vector<Zone *>>::iterator it = zones.begin();
    std::cout << getName() << ": " << std::endl;
    while (it != zones.end()) {
        std::cout << "\t" << it->first << ": " << std::endl;
        for (Zone *z: it->second) {
            std::cout << "\t\t" << z->getName() << "[" << z->getTotalDamage() << "]" << std::endl;   
        }
        it++;
    }
}

bool Theatre::checkForFaction(std::string factionName) {
    std::unordered_map<std::string, std::vector<Zone *>>::iterator it = zones.begin();
    while (it != zones.end()) {
        if (it->first == factionName) { return true; }
        it++;
    }
    return false;
}

void Theatre::printStrategies() {
    std::cout << getName() << ": " << std::endl;
    if (strategies.size() != 0) {
        std::unordered_map<std::string, WarStrategy *>::iterator it = strategies.begin();

        while (it != strategies.end()) {
            std::cout << "\t" << it->first << ": " << it->second->getType() << std::endl;
            it++;
        }

    } else {
        std::cout << getName() << " is Empty." << std::endl;
    }
}

int Theatre::getResource(std::string Faction) {
    return (checkForFaction(Faction)) ?  this->resource * calculateControl(Faction) : 0;   
}

float Theatre::calculateControl(std::string Faction) {
    if(!zones.count(Faction)){
       throw WarException("faction-not-found");
    }

    float ourSum = 0.0;
    float totalSum = 0.0;
    float final = 0.0;
    for (int i = 0; i < limit; i++) {
        
        ourSum = zones[Faction][i]->getTotalDamage();
        std::unordered_map<std::string, std::vector<Zone *>>::iterator it = zones.begin();

        while (it != zones.end()) {
            totalSum += it->second[i]->getTotalDamage();
            it++;
        }
        if(totalSum != 0){
            ourSum = ourSum / totalSum;
        }
        final += ourSum; 
    }
    return final / limit;
}

float Theatre::checkOpposition(std::string faction) {
    if(!zones.count(faction)){
       throw WarException("faction-not-found");
    }

    float ourSum = 0.0;
    float theirSum = 0.0;
    float totalSum = 0.0;
    float final = 0.0;
    for (int i = 0; i < limit; i++) {
        totalSum = 0;
        theirSum = 0;
        ourSum = zones[faction][i]->getTotalDamage();
        std::unordered_map<std::string, std::vector<Zone *>>::iterator it = zones.begin();
        while (it != zones.end()) {
            totalSum += it->second[i]->getTotalDamage();
            it++;
        }
        theirSum = totalSum - ourSum;
        if(totalSum != 0){
            theirSum = theirSum/totalSum;
        }
        final += theirSum;
    }
   
    return final / limit;
}

json Theatre::toJSON(int row, int col){
    std::string coordinates = std::to_string(row) + "-" + std::to_string(col);
    json data = json::array();
    std::unordered_map<std::string, std::vector<Zone *>>::iterator it = zones.begin();
    int landPower = 0;
    int seaPower = 0;
    int airPower = 0;
        while (it != zones.end()){
            if(limit == 3){
                    data.push_back(json{{"name", it->first},
                            {"landPower", it->second[0]->getTotalDamage()},
                            {"seaPower", it->second[2]->getTotalDamage()},
                            {"airPower", it->second[1]->getTotalDamage()}});
            }
            else{
                    data.push_back(json{{"name", it->first},
                            {"landPower", it->second[0]->getTotalDamage()},
                            {"seaPower", 0},
                            {"airPower", it->second[1]->getTotalDamage()}});
            }
            it++;
        }
    return json{{"name", getName()},
                {"coordinates", coordinates},
                {"data", data}};
}

std::string Theatre::getStrategy(std::string factionName){
   std::string type = strategies[factionName]->getType();
    if(type == "Attack"){
        return "Attack Strategy";
    } else if(type == "Counter"){
        return "Counter Strategy";
    } else if(type == "Plan"){
        return "Plan Strategy";
    } else{
        throw WarException("strategy-not-found");
    }
}

bool Theatre::checkForStrategy(std::string name){
    return (strategies[name]) ? true : false;
}

std::string Theatre::getTarget(std::string factionName){
    return strategies[factionName]->getTarget();
}
