#ifndef THEATRE_H
#define THEATRE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../exception/WarException.h"
#include "../faction/Faction.h"
#include "../utilities/uuid.h"

class Strategy;

class Theatre {
   protected:
    std::string name;
    std::string id;
    std::string type;
    std::vector<Faction*> factions;
    std::unordered_map<std::string, Strategy*> strategies;
    // In Country
    // map<TheatreID, Army>

    // In Theatre
    // vector<FactionID> occupants
    //
   public:
    Theatre(std::string name);
    void addFaction(Faction* faction);
    void removeFaction(Faction* faction);
    void battle();
    void setFactionStrategy(Faction* faction, Strategy* strategy);
    virtual ~Theatre();
};

#endif  // THEATRE_H