#ifndef WARENGINE_H
#define WARENGINE_H

#include "../faction/Country.h"
#include "../faction/Faction.h"
#include "../theatre/Theatre.h"
#include "../entity/factory/AirUnitFactory.h"
#include "../entity/factory/LandUnitFactory.h"
#include "../entity/factory/SeaUnitFactory.h"
#include "../entity/factory/UnitFactory.h"
#include "../utilities/json.hpp"

#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using json = nlohmann::json;

class Theatre;
class WarEngine {
   private:
        std::vector<Faction*> factions;
        // Faction* faction1;
        // Faction* faction2;
        Theatre*** theatres;
        int theatreSize;
        std::map<std::string, std::string>::iterator it;
        std::map<std::string, std::string> faction1UnitNames;
        std::map<std::string, std::string> faction2UnitNames;
        int turnCounter;
        bool player1Turn;

        std::unordered_map<std::string, UnitFactory*> unitFactories;
    
    // =============== Utility Functions ===============
        void addNames();
        void printMap();
        std::string toLower(std::string& str) const;

    // =============== Singleton =============== 
        WarEngine();    
        WarEngine(WarEngine&);
        WarEngine& operator=(WarEngine&);
        ~WarEngine();
    

   public:
       static WarEngine* instance();
   // ===================== SETUP =====================
    /**
        * @brief Instantiate factions
        * 
        * @param filePath Path to access json simulations file
        */

        void loadSimulation(json& simulation);

        
        
        /**
         * @brief Create Factions
         * 
         * @param faction1 Faction 1 name
         * @param faction2 Faction 2 name
         */
        void generateFactions(std::string faction1, std::string faction2);
        /**
         * @brief Set the Faction 1 Generic Unit Names
         * 
         * @param names String vector
         */
        void setFaction1UnitNames(std::vector<std::string> names);
        /**
         * @brief Set the Faction 2 Generic Unit Names
         * 
         * @param names String vector
         */
        void setFaction2UnitNames(std::vector<std::string> names);
        /**
         * @brief Set factions base resources
         * 
         * @param faction1BaseCount Faction 1 base resources
         * @param faction2BaseCount Faction 2 base resources
         */
        void setsFactionBaseResoures(int faction1BaseCount, int faction2BaseCount);

        // =====================JSON UTILITIES==============
        /**
         * @brief Convert json object to string vector
         * 
         * @param array A json object to be converted
         * @return std::vector<std::string> 
         */
        std::vector<std::string> setToString(json array);
        int setToInteger(std::string data);

        // ====================MAIN WAR FUNCTIONS===========
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

        // ===================UTILITY FUNCTIONS==============
        void viewStrategies();
        void displayUnits();
        void displayUnitMenu();
    
};

#endif  // WARENGINE_H