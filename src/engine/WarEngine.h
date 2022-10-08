#ifndef WARENGINE_H
#define WARENGINE_H
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include "../faction/Faction.h"

class Theatre;
class WarEngine {
    private:

        Faction * player1;
        Faction * player2;

        std::vector<Theatre*> theatres;
        std::map<std::string,std::string>::iterator it;
        std::map<std::string,std::string> player1UnitNames;
        std::map<std::string,std::string> player2UnitNames;
        int turnCounter;
        bool player1Turn;
        


    public:
        WarEngine();
        //Main War loop
        void startSimulation();
        //Set Names of players countries that were input in client
        void setCountryNames(std::pair<std::string,std::string> names);
        //Set Generic Unit Names for each player - was input in client
        void setPlayer1UnitNames(std::vector<std::string> names);
        void setPlayer2UnitNames(std::vector<std::string> names);
        void displayResources();
        void chooseStrategies();
        void CommenceBattle();
        ~WarEngine();

};

#endif // WARENGINE_H