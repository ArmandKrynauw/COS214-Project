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

class WarEngine {
   private:
        std::vector<Faction*> factions;
        Theatre*** theatres;
        int theatreSize;
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> countryUnitNames;
        std::unordered_map<std::string, UnitFactory*> unitFactories;
    
        int turnCounter;
        bool player1Turn;

    
        // =============== Utility Functions ===============
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
         * Provides functionality to load a war simulation from a JSON object. 
         * 
         * @param simulation JSON object containing simulation
        */
        void loadSimulation(const json& simulation);
        /**
         * Provides functionality to load countries from a JSON array. 
         * 
         * @param simulation JSON array containing country details
        */
        void loadCountries(const json& countries);
        void loadFactions(const json& factions);

        // =====================JSON UTILITIES==============
        /**
         * @brief Convert json object to string vector
         * 
         * @param array A json object to be converted
         * @return std::vector<std::string> 
         */
        std::vector<std::string> setToString(json array);

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