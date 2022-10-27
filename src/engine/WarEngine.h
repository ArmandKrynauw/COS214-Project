#ifndef WARENGINE_H
#define WARENGINE_H

#include "../faction/Country.h"
#include "../faction/Faction.h"
#include "../theatre/Theatre.h"
#include "../entity/factory/AirUnitFactory.h"
#include "../entity/factory/LandUnitFactory.h"
#include "../entity/factory/SeaUnitFactory.h"
#include "../entity/factory/UnitFactory.h"

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
    void placeEntities();
    void chooseStrategies();
    void CommenceBattle();
    ~WarEngine();
};

#endif  // WARENGINE_H