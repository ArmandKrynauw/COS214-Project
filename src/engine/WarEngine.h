#ifndef WARENGINE_H
#define WARENGINE_H

#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "../entity/factory/AirUnitFactory.h"
#include "../entity/factory/LandUnitFactory.h"
#include "../entity/factory/SeaUnitFactory.h"
#include "../entity/factory/UnitFactory.h"
#include "../escalation/EarlyStage.h"
#include "../escalation/Escalation.h"
#include "../faction/Alliance.h"
#include "../faction/Country.h"
#include "../faction/Faction.h"
#include "../theatre/Theatre.h"
#include "../utilities/json.hpp"

using json = nlohmann::json;

class WarEngine {
   private:
    std::unordered_map<std::string, Alliance*> alliances;
    std::unordered_map<std::string, Country*> countries;
    Theatre*** theatres;
    Escalation* warStage;
    int theatreSize;

    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> countryUnitNames;
    std::unordered_map<std::string, UnitFactory*> unitFactories;

    std::vector<json> simulations;
    int currentSimulation;
    int currentDay;
    bool beforeBattle;

    // =============== Singleton ===============
    WarEngine();
    WarEngine(WarEngine&);
    WarEngine& operator=(WarEngine&);
    ~WarEngine();

   public:
    static WarEngine* instance();

    // =================== WAR ENGINE CONTROL FUNCTIONS ===================

    /**
     * Load necessary data for next battle day in preparation for Theatre
     * battles to take place.
     *
     * @throws WarException if a simulation has not been loaded
     * @throws WarException if end of simulation has been reached
     * @throws WarException if next battle is loaded before results are displayed
     */
    void loadNextBattleDay();

    /**
     * Provides functionality to initiate a battle in all theatres
     * 
     * @throws WarException if results are loaded before battle day is loaded
     */
    void loadBattleDayResults();

    /**
     * Will revert the engine state back to the start of the previous battle
     * day. If the simulation is at the start then nothing will happen.
    */
    void loadPreviousBattleDay();

    /**
     * Will load any specific battle day state. A pre-defined simulation
     * is needed for this method to function correctly.
    */
    void loadSpecificBattleDay(int index);

    // ====================== LOAD SIMULATIONS ======================

    /**
     * Provides functionality to load all simulations from JSON array
     * into a vector of json objects.
     * @throws WarException If file containing simulations is not found
     * @throws WarException If json object cannot be parsed from file
     * 
     */
    void loadSimulations();
    /**
     * Provides functionality to call loadSimulation() with a specific simulation
     * by using index to get at simulations[index] and parse into loadSimulation().
     * 
     * @param index The index of chose simulation in simulations vector
     */
    void selectSimulation(int index);

    /** Provides functionality to get a list of available simulations to be
     * loaded into the engine. Also includes additional information about each
     * simulation like Countries and Alliances partaking in the simulation. See
     * https://demo.hedgedoc.org/enrh8j-uSU6jJ3V8m6NHWw#Available-Simulations
     * 
     * @return JSON array containing available simulations
    */
    json getAvailableSimulations();

    /**
     * Provides functionality to clear all members in the War Engine. This
     * enables new simulations to be loaded or a simulation to be restarted
     * without the need to restart the whole engine.
    */
    void reset();

    /**
     * Provides functionality to load theatre objects from a JSON array.
     * The objects consist of a Theatre name, boolean field to specify if there
     * is water in the theatre area and a resource count. (e.g. { "name":
     * "Sicily", "seaZone": true, "resourceCount": 10 })
     *
     * @param data JSON array containing theatres
     */
    void loadTheatres(const json& data);

    /**
     * Provides functionality to load the initial war simulation setup from
     * a JSON object. This initial setup includes loading Countries and
     * Alliances. Can be expanded to meet missing requirements.
     *
     * @param simulation JSON object containing simulation
     */
    void loadSimulation(const json& data);

    /**
     * Provides functionality to load country objects from a JSON array.
     * The objects consist of a Country's name, unit names, and base resource
     * count.(e.g.  {"name": "Germany", "countryCode": "GER",
                    "units": [
                        { "HeavyAirUnit": "Luftwaffe A400M" },
                        { "HeavyLandUnit": "Leopard 2A7" },
                        { "HeavySeaUnit": "Type 212 Submarine" },
                        { "LightAirUnit": "CH-53G" },
                        { "LightLandUnit": "Foot Soldier" },
                        { "LightSeaUnit": "Baden-Württemberg class" },
                        { "MediumAirUnit": "Eurofighter Typhoon" },
                        { "MediumLandUnit": "BMP-3" },
                        { "MediumSeaUnit": "Braunschweig class" }
                    ],"baseResourceCount": 1000})
     *
     * @param data JSON array containing country objects
     */
    void loadCountries(const json& data);

    /**
     * Provides functionality to load Alliance objects from a JSON array.
     * The objects consist of an Alliance's name and an array containing all
     * the names of Countries in the Alliance.
     * (e.g. {"name": "Allies","countries": ["America", "France"]})
     *
     * @param simulation JSON array containing Alliance objects
     */
    void loadAlliances(const json& data);

    /**
     * Provides functionality to load Escalation and Mobilization
     * for each country for the current war day.
     *
     * @param data JSON Object of current war day
     */
    void loadWarFactors(const json& data);

    /**
     * Provides functionality to load new mobilization levels per country from a
     * JSON array. Each object in the array consists of the country name and the
     * new mobilization level. (e.g. {"name": "Germany", "mobilization":
     * "PartialMobilization"})
     *
     * @param data JSON Object containing a JSON array of countries and their
     * respective new mobilization levels
     */
    void loadMobilization(const json& data);

    /**
     * Provides functionality to add new Research for each country from a JSON
     * array Each object in the array has a country name, the category they want
     * to research and the amount of resources they want to spend. (e.g.
     * {"name": "Germany","research": "industry","points": 50})
     *
     * @param data JSON object containing a countries JSON array
     */
    void loadResearch(const json& data);

    /**
     * Provides functionality to load a new Escalation stage for the current war
     * day using the warState property. The stages may be "EarlyStage",
     * "MiddleStage" or "LateStage". (e.g. "WarState": "EarlyStage")
     *
     * @param data JSON property
     */
    void loadEscalation(const json& data);

    /**
     * Provides functionality for Countries to purchase units. This method
     * expects a JSON array of objects. Each object requires the name of the
     * Country and an array of units to purchase.
     * (e.g. {"name": "Germany","units": []})
     *
     * @param data JSON array containing units to purchase for each Country
     * @throws WarException if request was malformed
     * @throws WarException if Country does not have sufficient resources
     */
    void purchaseUnits(const json& data);

    /**
     * Provides functionality to move units per country to different theatres
     * from a JSON array. Each object in the array has a country name and a JSON
     * array of movements. Each movement consists of the type of troop, the
     * coordinates of a theatre in "row,column" format and the index of the unit
     * in the countries vector. (e.g. {"name": "Germany"," movements": [{"type":
     * "land", "index": 0,"destination": "1,0"}]})
     *
     * @param data JSON array containing units to move and their destinations
     * @throws WarException if request was malformed
     */
    void relocateUnits(const json& data);

    /**
     * Provides functionality to transport a unit out of a theatre and into a
     * new theatre or from the home country to a theatre.
     *
     * @param destination The final destination of the unit
     * @param country The country that created the unit
     * @param type The type of unit: (e.g. land, sea or air)
     * @param id  The index of the unit in country vector
     */
    void transportUnit(Theatre* destination, const std::string& country,
                       const std::string& type, const int& index);

    /**
     * Provides functionality to generate Entities for specific Countries.
     *
     * @param country Name of Country
     * @param type Type of Unit to create (e.g. HeavyLandUnit)
     * @param special A field that is filled if a unit has the "special"
     * property where then the entity is decorated as Engineers or FieldHospital
     *  (e.g. { "type": "HeavyLandUnit", "quantity": 1 })
     *  (e.g. { "type": "MediumLandUnit", "quantity": 2 , "special" :
     * "engineers"})
     *
     * @throws WarException if Country or Type is not found
     */
    Entity* generateUnit(const std::string& country, const std::string& type,
                         const std::string& special);

    /**
     * Provides functionality generateResources for each country. Each theatre
     * has resources and depending on a countries control in said theatres, a
     * percentage of resources is given to that country. For each theatre this
     * is added to the countries resources. For alliances all countries extra
     * resources are shared equally among all countries in the alliance. This
     * function is called before each new War Day takes place.
     */
    void generateCountryResources();

    /**
     * Provides functionality to assign strategies to theatres from a JSON
     * array. Each object in the array has a country name and a strategies JSON
     * array. Each object in the strategies array has a Strategy (e.g. Attack)
     * and a theatre represent as coordinates (e.g. 0,0 for Sicily) and a target
     * country the strategy is applied to (e.g. Germany). (e.g. {"name": "United
     * Kingdom", "strategies": [{"strategy": "Attack", "theatre": "0,0",
     * "target": "Germany"}]})
     *
     * @param data JSON array of countries and their strategies
     * @throws WarException if the strategy is not found
     */
    void assignStrategies(const json& data);

    // ====================== JSON UTILITIES ======================

    /**
     * General function to return current state of Engine in JSON
     *
     * @return json All statistics in JSON
     */
    json getStats();

    /**
     * Get the Engine statistics
     *
     * @return json Statistics in JSON
     */
    json getEngineStats();

    /**
     * Get the Country statistics
     *
     * @return json Statistics in JSON
     */
    json getCountryStats();

    /**
     * Get the Alliance statistics
     *
     * @return json Statistics in JSON
     */
    json getAllianceStats();

    /**
     * Get all unit statistics
     *
     * @return json Statistics in JSON
     */
    json getOverallUnits();

    /**
     * Get the Theatre statistics
     *
     * @return json Statistics in JSON
     */
    json getTheatreStats();

    /**
     * Get the Strategies statistics
     *
     * @return json Statistics in JSON
     */
    json getStrategies();

    /**
     * Get the Mobilization statistics
     *
     * @return json Statistics in JSON
     */
    json getMobilization();

    /**
     * Get the Research statistics
     *
     * @return json Statistics in JSON
     */
    json getResearch();

    /**
     * Provides functionality to generate a JSON array of the current Unit
     * states for each Country sorted by Theatre.
     *
     * @return JSON array with each Country's units
     */
    json getTheatreUnits();

    /**
     * Will clear all casualties from countries and generate a JSON report
     * of the casualties that occurred for each Country sorted by Theatre.
     * This method has to be called after every battle day.
     *
     * @return JSON array with each Country's casualties
     */
    json clearCasualties();

    // ====================== UTILITY FUNCTIONS ======================

    /**
     * Helper function to view strategies for a theatre per country
     *
     */
    void viewStrategies();

    /**
     * Provides functionality to convert coordinates of a theatre
     * to an int pair.(e.g. 0,0 converted to std::pair<int,int>(0,0))
     *
     * @param data Location of theatre in JSON
     * @return std::pair<int,int> Location in std::pair<row,column> format
     */
    std::pair<int, int> getLocation(const json& data);

    Theatre * findTheatre(std::string theatreName);

    // ====================== TESTING FUNCTIONS ======================

    Theatre* TestTheatre();
};

#endif  // WARENGINE_H