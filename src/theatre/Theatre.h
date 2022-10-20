#ifndef THEATRE_H
#define THEATRE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../exception/WarException.h"
#include "../faction/Faction.h"
#include "../utilities/uuid.h"
#include "../war-strategy/WarStrategy.h"
#include "../zone-factory/AirZoneFactory.h"
#include "../zone-factory/LandZoneFactory.h"
#include "../zone-factory/SeaZoneFactory.h"
#include "../entity/product/Unit.h"
#include "Zone.h"
#include <map>

class Strategy;

class Theatre
{
protected:
    std::string name;
    std::string id;
    int limit;
    std::vector<std::vector<Zone*>> armies;
    std::map<std::string, int> factions;  //key -> name, value -> index
    std::vector<Strategy*> strategies;
    AirZoneFactory* airFactory;
    LandZoneFactory* landFactory;
    SeaZoneFactory* seaFactory;
public:
    Theatre(std::string name, bool seaZone);
    void addFaction(std::string name);
    void removeFaction(std::string name);
    void addUnit(std::string faction,Unit* unit);
    Unit* removeUnit(std::string faction,int type,int index);
    std::string getName() const;
    float changeStrategy(int num);
    void Battle(std::string attacker,std::string defender);
    virtual ~Theatre();
};


#endif // THEATRE_H