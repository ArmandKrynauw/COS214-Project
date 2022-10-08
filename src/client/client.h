#ifndef CLIENT_H
#define CLIENT_H
#include <map>
#include <iterator>
#include <iostream>
#include <vector>


class Client{

    private:
        std::map<std::string, std::vector<std::string> > countries;
        //WarEngine * engine;
        std::vector<std::string> availableCountries;
    public:
        Client();
        //Main Client Function called by our "Embedded Hardware" Class, main.cpp
        void Run();
        std::vector<std::string> getCoutryUnits(std::string countryName);
        //Return a pair of country names that player 1 and player 2 choose respectively
        std::pair<std::string,std::string> getPlayerCountries();

        void printHeader();
        void printFooter();
};
#endif // CLIENT_H