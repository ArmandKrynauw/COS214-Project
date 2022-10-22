#ifndef THEATRE_H
#define THEATRE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../utilities/WarException.h"
#include "../faction/Faction.h"
#include "../utilities/uuid.h"
#include "../war-strategy/PlanStrategy.h"
#include "../war-strategy/CounterStrategy.h"
#include "../war-strategy/AttackStrategy.h"
#include "../zone-factory/AirZoneFactory.h"
#include "../zone-factory/LandZoneFactory.h"
#include "../zone-factory/SeaZoneFactory.h"
#include "Zone.h"
#include <map>


class Theatre
{
private:
    std::string name;
    std::string id;
    int limit;
    // std::vector<std::vector<Zone*>> armies;
    std::unordered_map<std::string, std::vector<Zone*>> armies;
    //std::map<std::string, int> factions;  //key -> name, value -> index
    // std::vector<std::string>factions;
    // std::vector<WarStrategy*> strategies;
    std::unordered_map<std::string, WarStrategy*> strategies;
    AirZoneFactory* airFactory;
    LandZoneFactory* landFactory;
    SeaZoneFactory* seaFactory;
    void addFaction(std::string name);
    void removeFaction(std::string name);
public:
    Theatre(std::string name, bool seaZone);
    void addUnit(std::string faction ,Unit* unit);
    Unit* removeUnit(std::string faction, std::string type, int index);
    std::string getName() const;
    void changeStrategy(std::string faction, WarStrategy* strategy);
    void Battle(std::string attacker,std::string defender);
    virtual ~Theatre();
};


#endif // THEATRE_H