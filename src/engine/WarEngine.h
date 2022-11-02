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
#include "../faction/Alliance.h"
#include "../faction/Country.h"
#include "../faction/Faction.h"
#include "../theatre/Theatre.h"
#include "../utilities/json.hpp"
#include "../escalation/Escalation.h"
#include "../escalation/EarlyStage.h"

using json = nlohmann::json;

class WarEngine {
private:
    std::unordered_map<std::string, Alliance *> alliances;
    std::unordered_map<std::string, Country *> countries;
    Theatre ***theatres;
    int theatreSize;

    Escalation *warStage;
    // Depreciated!!!!
    std::vector<Faction *> factions;

    std::unordered_map<std::string,
            std::unordered_map<std::string, std::string>>
            countryUnitNames;
    std::unordered_map<std::string, UnitFactory *> unitFactories;

    int roundCounter;
    bool player1Turn;
    int warDuration;


    // =============== Utility Functions ===============
    void printMap();

    std::string toLower(std::string &str) const;

    // =============== Singleton ===============
    WarEngine();

    WarEngine(WarEngine &);

    WarEngine &operator=(WarEngine &);

    ~WarEngine();

public:
    static WarEngine *instance();

    // ====================== LOAD SIMULATIONS ======================

    void loadTheatres(const json& theatres);
    /**
     * Provides functionality to load the initial war simulation setup from
     * a JSON object. This initial setup includes loading Countries and
     * Alliances. Can be expanded to meet missing requirements.
     *
     * @param simulation JSON object containing simulation
     */
    void loadSimulation(const json &simulation);

    /**
     * Provides functionality to load country objects from a JSON array.
     * The objects consist of a Country's name, unit names, and base resource
     * count.
     *
     * @param data JSON array containing country objects
     */
    void loadCountries(const json &data);

    /**
     * Provides functionality to load Alliance objects from a JSON array.
     * The objects consist of an Alliance's name and an array containing all
     * the names of Countries in the Alliance.h
     *
     * @param simulation JSON array containing Alliance objects
     */
    void loadAlliances(const json &data);

    void checkMobilization(const json& data);


    /**
     * Provides functionality for Countries to purchase units. This method
     * expects a JSON array of objects. Each object requires the name of the
     * Country and an array of units to purchase.
     *
     * @param data JSON array containing units to purchase for each Country
     * @throws WarException if request was malformed
     * @throws WarException if Country does not have sufficient resources
     */
    void purchaseUnits(const json &data);

    /**
     * @brief Provides functionality for Countries to relocate troops to different
     * theatres.
     * 
     * @param data JSON array containing units to move and their destinations
     * @throws WarException if request was malformed
     */
    void relocateUnits(const json &data);

    /**
     * Provides functionality to generate Units for specific Countries.
     *
     * @param country Name of Country
     * @param type Type of Unit to create (e.g. HeavyLandUnit)
     *
     * @throws WarException if Country or Type is not found
     */
    Unit *generateUnit(const std::string &country, const std::string &type);

    /**
     * This method will be called each round before the simulation proceeds to
     * the purchase Unit phase.
    */
    void generateCountryResources(const json& c,const json& a);



    // ====================== JSON UTILITIES ======================
    /**
     * This method calls all the stats getters to generate on big stats object
    */
    //Complete
    json getStats();
    json getEngineStats();
    json getCountryStats();
    json getAllianceStats();
    json getOverallUnits();
    json getTheatreStats();

    /**
     * Provides functionality to generate a JSON array of the current Unit
     * states for each Country sorted by Theatre.
     *
     * @return JSON array with each Country's units
    */
    json getTheatreUnits();

   
    
    json getCasualties();

    /**
     * @brief Convert json object to string vector
     *
     * @param array A json object to be converted
     * @return std::vector<std::string>
     */
    std::vector<std::string> setToString(json array);

    /**
     * @brief Convert JSON object to pair of int
     * 
     * @param data location of unit in json format
     * @return std::pair<int,int> 
     */
    std::pair<int, int> getLocation(const json &data);

    /**
     * @brief Transport a unit between to theatres or home base and a theatre
     * 
     * @param destination The final destination of the unit
     * @param country The country the unit fights for
     * @param type The type of unit being land, sea or air
     * @param id  The index of the unit in the list to move
     */
    void transportUnit(Theatre *destination, const std::string &country, const std::string &type, const int &index);

    void assignStrategies(const json &data);

   

    

    void checkEscalation(const json &data);

    // ====================== MAIN WAR FUNCTIONS ======================

    void startSimulation(json war);

    /**
     * @brief Display Faction Resources
     *
     */
    void displayResources();

    /**
     * @brief Allow Faction to Buy Units
     *
     */
    void buyUnits();

    /**
     * @brief Allow Factions to transport troops to theatres
     *
     */
    void placeTroops();

    /**
     * @brief Allow Factions to select Strategies for theatres
     *
     */
    void chooseStrategies();

    /**
     * @brief Commence all battles in active theatres
     *
     */
    void CommenceBattle();

    json clearCasualties();

    json getRoundResults();

    // ====================== UTILITY FUNCTIONS ======================
    void debug();

    void viewStrategies();

    void displayUnits();

    void displayUnitMenu();
};

#endif  // WARENGINE_H