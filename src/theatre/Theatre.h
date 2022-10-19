#ifndef ZONE_H
#define ZONE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../exception/WarException.h"
#include "../faction/Faction.h"
#include "../utilities/uuid.h"

class Strategy;

class Theatre
{
protected:
    std::string name;
    std::string id;
    std::string type;
    std::vector<Faction *> factions;
    std::unordered_map<std::string, Strategy *> strategies;
    // In Country
    // map<ZoneID, Army>

    // In Zone
    // vector<FactionID> occupants
    //
public:
    Theatre(std::string name, std::string type);
    virtual ~Theatre();
};

#endif // THEATRE_H