#ifndef THEATRE_H
#define THEATRE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../utilities/WarException.h"
#include "../faction/Faction.h"
#include "../utilities/uuid.h"
#include "../utilities/json.hpp"
#include "../war-strategy/PlanStrategy.h"
#include "../war-strategy/CounterStrategy.h"
#include "../war-strategy/AttackStrategy.h"
#include "../zone-factory/AirZoneFactory.h"
#include "../zone-factory/LandZoneFactory.h"
#include "../zone-factory/SeaZoneFactory.h"
#include "Zone.h"
#include <map>

using json = nlohmann::json;
class Theatre {
private:
    std::string name;
    std::string id;
    int limit;
    int resource;
    std::unordered_map <std::string, std::vector<Zone *>> zones;
    std::unordered_map<std::string, WarStrategy *> strategies;
    AirZoneFactory *airFactory;
    LandZoneFactory *landFactory;
    SeaZoneFactory *seaFactory;

    /**
     * Provides functionality to add a Faction to a Theatre. Respective Zones
     * will be generated for each Faction when it gets added to a Theatre. This
     * method is called by the addUnit if notices that a Faction has not
     * been added to a Theatre yet. If the Faction already exists then nothing
     * will happen.
     * 
     * @param name Name of the Faction to be added
    */
    void addFaction(std::string name);

    /**
     * Provides functionality to remove a Faction from a Theatre. The Factions's
     * respective Zones will be removed from the Theatre. This method is called
     * by removeUnit if it notices that a Faction does not have any Units left
     * over in the current Theatre.
     * 
     * @param name Name of the Faction to be removed
    */
    void removeFaction(std::string name);


    /**
     * Provides functionality to get the percentage control of a faction in this threatre
     * @param faction Name of the faction whose percentage control needs to be returned
     * @return The percentage as a float : i.e 0.45
     * 
     */

    float calculateControl(std::string faction);

public:


    Theatre(std::string name, bool seaZone, int resource);

    /**
     * Provides functionality to add a Unit from a Faction to a specific
     * Theatre. If the Faction does not have any Zones in the current Theatre
     * then the addFaction method will be called.
     * 
     * @param faction Name of the faction to be added
     * @param unit Unit to be add to the Theatre
    */
    void addEntity(std::string faction, Entity *unit);

    /**
     * Provides functionality to remove a specific Faction's Unit from a
     * Theatre. If the Faction has no more Units stationed in this Theatre then
     * the Faction's Zones will be removed by call removeFaction.
     *
     * @param faction Name of Faction Unit to be removed
     * @param type Type of Unit which has to be removed
     * @param id The id of the Unit to be removed in the Zone
     *
     * @return The removed Unit
     * @throws WarException if index is out of bounds or if Unit is not found
    */
    Entity *removeEntity(std::string faction, std::string type, std::string id);

    std::string getName();

    std::string getId() const;

    /**
     * Provides functionality to change the War Strategy for a specific Faction
     * for the next round of the war.
     * 
     * @param faction Name of the faction whose Strategy has to be changed
     * @param strategy The new Strategy
    */
    void changeStrategy(std::string faction, WarStrategy *strategy);

    /**
     * Provides functionality to simulate battles taking place for each turn in
     * the war. All the Factions in the Theatre will be iterated through and
     * their Strategies will be executed against the opposing Factions in the
     * Theatre.
    */
    void battle();

    /**
     * Provides functionality to get the amount of resources a faction earns of the resource pool of a threatre
     * @param faction Name of the faction whose resources portion needs to be returned
     * @return The resources portion of the specified faction for this threatre 
     * 
     */

    int getResource(std::string faction);


    /**
     * Provides functionality to display the internals of a theatre. This being troop count per faction and theatre name.
     * 
     */
    void printTheatre();

    bool checkForFaction(std::string factionName);

    void printStrategies();

    json toJSON(int row, int col);

    virtual ~Theatre();
};

#endif // THEATRE_H