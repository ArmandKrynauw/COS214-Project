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
     * Provides functionality to get the percentage control of a faction in this theatre
     * 
     * @param faction Name of the faction whose percentage control needs to be returned
     * @return The percentage as a float (e.g. 0.45)
     * 
     */

    float calculateControl(std::string faction);

    /**
     * Provides functionality to get the percentage control that all other factions have in this theatre
     * 
     * @param faction Name of the faction whose opposition we want to check
     * @return The percentage as a float (e.g. 0.45)
     */

    float checkOpposition(std::string faction);


public:

    /**
     * Provides functionality to create a Theatre object.
     * 
     * @param name Name of theatre (e.g. Sicily)
     * @param seaZone If the theatre has ocean access (e.g. true)
     * @param resource Resources that a theatre provides to countries (e.g. 40)
     */
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

    /**
     * Provides functionality to get the name of the theatre
     * 
     * @return string Name of the Theatre
     */

    std::string getName();

    /**
     * Provides functionality to get the unique uuid of the theatre
     * 
     * @return string Id of theatre
     */

    std::string getId() const;

    /**
     * Provides functionality to change the War Strategy for a specific Faction
     * for the next day of the war.
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
     * Provides functionality to get percentage of resources a faction will receive. 
     * 
     * @param faction Name of the faction whose resources portion needs to be returned
     * @return Portion of resource given to the faction 
     */

    int getResource(std::string faction);


    /**
     * Provides functionality to display the internals of a theatre. This being troop count per faction and theatre name.
     * 
     */
    void printTheatre();

    /**
     * Provides functionality to check whether a faction is in the theatre.
     * 
     * @param factionName The name of the faction to check as a string
     * @return true Return if faction is in theatre
     * @return false Return if faction is not in theatre
     */

    bool checkForFaction(std::string factionName);

    /*
     * Provides functionality to display the strategies that each faction currently executes
     */

    void printStrategies();

    /**
    * Provides functionality to return a json object containing data of the theatre
    * 
    * @param row Row index of theatre in array
    * @param col Column index of theatre in array
    * @return json JSON Object
    * 
    */
    json toJSON(int row, int col);
    /**
     * Provides functionality to return the strategy for a given faction in string format.
     * (e.g. If AttackStrategy object then return "Attack Strategy")
     * 
     * @param factionName Name of faction to get strategy
     * @return std::string Return string format of strategy
     */
    std::string getStrategy(std::string factionName);
    /**
     * Provides functionality to check if a faction has given a strategy for the theatre.
     * 
     * @param name Check if faction with this name has a strategy
     * @return true Return if faction has a strategy
     * @return false Return if faction does not have a strategy
     */
    bool checkForStrategy(std::string name);
    /**
     * Provides functionality to provide the target for the strategy in the theatre
     * for the passed in faction.
     * 
     * @param factionName Name of a faction
    */
    std::string getTarget(std::string factionName);

    virtual ~Theatre();
};

#endif // THEATRE_H