#include "Country.h"

#include "../entity/product/Entity.h"
#include "../entity/product/Unit.h"
#include "../theatre/Theatre.h"
#include "../faction/Alliance.h"

Country::Country(std::string name) : Faction(name) {
    armedForces["land"] = new ArmedForce("Army", "land");
    armedForces["sea"] = new ArmedForce("Navy", "sea");
    armedForces["air"] = new ArmedForce("Air Force", "air");
    this->mobilization = new PartialMobilization("pre-war");
    alliance = NULL;
    baseResourceCount = 0;
    resourceCount = 0;
}

void Country::setMobilization(std::string mobilization) {
    this->mobilization->setState(mobilization);
}

void Country::checkMobilization(std::string warState, std::string newMobilization) {
    this->mobilization = this->mobilization->checkWarState(warState,newMobilization);
}

void Country::generateResources(int theatreResource) {
    //resourceCount += baseResourceCount;
    // 500 * 0.3
    resourceCount += baseResourceCount * mobilization->getIndustryModifier() + theatreResource;
}

int Country::getResourceCount() {
    return resourceCount;
}

void Country::setBaseResourceCount(int baseResourceCount) {
    this->baseResourceCount = baseResourceCount;
}

void Country::setResearch(int researchPoints,std::string category) {

    if(!((resourceCount - researchPoints) > 0)){
        throw WarException("Insufficient-Resources");
    }

    this->resourceCount -= researchPoints;

    if(inAlliance()){

        alliance->setResearch(researchPoints,category);

        if(alliance->getResearch(0)>=500)
        {
            alliance->resetResearch(0);
            for(Faction * m : alliance->getMembers()){
                m->setBaseResourceCount(m->getBaseResourceCount() * 1.2);
            }
            
        }
        if(alliance->getResearch(1)>=500)
        {
            alliance->resetResearch(1);
            for(Faction * m : alliance->getMembers()){
                m->setMorale(m->getMorale() * 1.2);
            }
        }
       return; 
    }
    

    Faction::setResearch(researchPoints,category);

    if(getResearch(0)>=500)
    {
        resetResearch(0);
        setBaseResourceCount(getBaseResourceCount() * 1.2);
    }
    if(getResearch(1)>=500)
    {
        resetResearch(1);
        setMorale(getMorale() * 1.2);
    }
    
}

int Country::getResearch(int i) {
    return research[i];
}

void Country::resetResearch(int index) {
    research[index] -= 500;
}

Alliance * Country::getAlliance() {
    return alliance;
}

void Country::addEntity(Entity *entity) {
    if (resourceCount - entity->getValue() < 0) {
        throw WarException("Insufficient resources available.",
                           "insufficient_resources");
    }
    resourceCount -= entity->getValue();
    armedForces[entity->getType()]->add(entity);
}

void Country::removeEntity(Entity *entity) {
    if (entity) {
        armedForces[entity->getType()]->remove(entity);
    }
}

Entity *Country::getEntity(const std::string &type, const int &index) {
    if (armedForces[type]->getUnitCount() - 1 < index || index < 0) {
        throw WarException("out-of-bounds");
    }
    return armedForces[type]->getEntity(index);
}

void Country::clearCasualties() {
    std::unordered_map<std::string, ArmedForce *>::iterator it;
    for (it = armedForces.begin(); it != armedForces.end(); ++it) {
        it->second->clearCasualties();
    }
}

int Country::getEntityCount() {
    int count = 0;
    std::unordered_map<std::string, ArmedForce *>::iterator it;
    for (it = armedForces.begin(); it != armedForces.end(); ++it) {
        count += it->second->getUnitCount();
    }
    return count;
}

bool Country::checkForArmedForces() {
    return (armedForces["land"]->getUnitCount() == 0 && armedForces["air"]->getUnitCount() == 0 && armedForces["sea"]->getUnitCount() == 0) ? false : true;
}

// ==================JSON HELPER FUNCTIONS===========

json Country::getListOfUnits() {
    json data = json{
            {"name",  name},
            {"theatres", json::array()}
    };
    json units;

    std::unordered_map<std::string, ArmedForce *>::iterator it;
    for (it = armedForces.begin(); it != armedForces.end(); ++it) {
        json j = it->second->toJSON();
        for (json u: j) {
            std::string theatre = u["theatre"];
            if (!units.contains(theatre)) {
                units[theatre] = json::array();
            }

            u.erase("theatre");
            units[theatre].push_back(u);
        }
    }

    json::iterator theatreIt = units.begin();
    for (; theatreIt != units.end(); ++theatreIt) {
        data["theatres"].push_back(json{
                {"name", theatreIt.key()},
                {"units",   theatreIt.value()}
        });
    }

    return data;
}

json Country::allUnitsToJSON() {
    if(!checkForArmedForces()){
        return json::array();   
    }
    json array;

    std::unordered_map<std::string, ArmedForce *>::iterator it;
    for (it = armedForces.begin(); it != armedForces.end(); ++it) {
        for (Entity* e: it->second->getEntities()) {
            array.push_back(e->unitToJSON());
        }
    }
    return array;
}

void Country::joinAlliance(Alliance * a) {
    alliance = a;
}

void Country::leaveAlliance() {
    alliance = NULL;
}

bool Country::inAlliance() {
    return (alliance) ? true : false;
}

std::string Country::getMobilization() {
    return mobilization->getState();
}

json Country::researchToJSON() {
    int industry = 0;
    int propaganda = 0;
    if(inAlliance()){
        industry = alliance->getResearch(0);
        propaganda = alliance->getResearch(1);
    }
    else{
        industry = getResearch(0);
        propaganda = getResearch(1);
    }
    return json{{"name", name},
                {"industryCurrent", industry},
                {"propagandaCurrent", propaganda},
                {"researchGoal", 500}};
}

Country::~Country() {}

