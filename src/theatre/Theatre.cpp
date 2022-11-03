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

    // TODO: Check if Faction has any Units left in the Theatre
    // after a Unit has been removed. If it doesn't then remove the Faction
    // and its zones from the Theatre.

    // bool removeFaction = true;
    // for (int i = 0; i < factionZones.size(); i++) {
    //     if (factionZones[i]-size() > 0) {

    //     }
    // }

    entity->setTheatre(NULL);
    return entity;
}

void Theatre::battle() {

    std::unordered_map<std::string, WarStrategy *>::iterator it = strategies.begin();
    if (strategies.size() > 1) {
        //std::cout<<getName()<<" has a battle."<<std::endl;
        while (it != strategies.end()) {
            if(it->second && strategies[it->second->getTarget()]){
                std::string attacker = it->first;                   //America
                std::string defendant = it->second->getTarget();    //Germany
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
                        zones[attacker][i]->takeDamage(defendFinal);  // defender deals damage

                        //zones[defendant][i]->takeDamage(attackFinal);  // attacker deals damage
                    }
                }
            }
            it++;
        }
    } else if (strategies.size() == 1) {
        //When Only one faction has a strategy
    } else {
        //Nobody in Theatre
        //std::cout<<getName()<<" is neutral."<<std::endl;
    }

    //results?
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
            // int sum = 0;
            // for(Unit* u: z->getUnits()){
            //     sum+=u->getHP();
            // }
            // std::cout<<sum<<std::endl;
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
    //std::cout<<std::endl;
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
        //std::cout<<"Theatre: "<<name<<" "<<totalSum<<std::endl;
        
        if(totalSum != 0){
            ourSum = ourSum / totalSum;
        }
        final += ourSum;
        
    }

    //std::cout<<"Theatre: "<<name<<" Faction: "<<Faction<<": "<<final/limit<<std::endl;
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
