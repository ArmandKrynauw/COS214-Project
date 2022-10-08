#ifndef WARENGINE_H
#define WARENGINE_H
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <iterator>

class Theatre;
class WarEngine {
    private:

        std::vector<Theatre*> theatres;
        std::map<std::string,std::string>::iterator it;
        std::map<std::string,std::string> player1UnitNames;
        std::map<std::string,std::string> player2UnitNames;

    public:
        WarEngine();
        void startSimulatino();
        void setPlayer1UnitNames(std::string arr[]);
        void setPlayer2UnitNames(std::string arr[]);
        ~WarEngine();

};

#endif // WARENGINE_H