#ifndef WARENGINE_H
#define WARENGINE_H

#include "../faction/Country.h"
#include "../faction/Faction.h"
#include "../theatre/Theatre.h"
#include "../unit-factory/Factory/AirUnitFactory.h"
#include "../unit-factory/Factory/LandUnitFactory.h"
#include "../unit-factory/Factory/SeaUnitFactory.h"
#include "../unit-factory/Factory/UnitFactory.h"

#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

class Theatre;
class WarEngine {
   private:
    Faction* faction1;
    Faction* faction2;
    std::vector<std::vector<Theatre*>> theatres;
    std::map<std::string, std::string>::iterator it;
    std::map<std::string, std::string> faction1UnitNames;
    std::map<std::string, std::string> faction2UnitNames;
    int turnCounter;
    bool player1Turn;

    std::unordered_map<std::string, UnitFactory*> unitFactories;

    // =============== Utility Functions ===============
    void addNames();
    std::string toLower(std::string& str) const;

   public:
    WarEngine();
    // Main War loop
    void startSimulation();
    // Set Names of players countries that were input in client
    void setCountryNames(std::pair<std::string, std::string> names);
    // Set Generic Unit Names for each player - was input in client
    void setFaction1UnitNames(std::vector<std::string> names);
    void setFaction2UnitNames(std::vector<std::string> names);
    // Set Starting Base Resource count
    void setsFactionBaseResoures(int faction1BaseCount, int faction2BaseCount);
    void displayResources();
    void buyUnits();
    void displayUnits();
    void displayUnitMenu();
    void placeTroops();
    void chooseStrategies();
    void CommenceBattle();
    ~WarEngine();
};

#endif  // WARENGINE_H