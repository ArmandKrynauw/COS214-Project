#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <iterator>
#include <map>
#include <vector>

#include "WarSocket.h"

using json = nlohmann::json;

class Client {
private:
    std::vector<json> simulations;
    std::map<std::string, std::vector<std::string> > countries;
    WarSocket *socket;
    std::vector<std::string> availableCountries;
    json chosenSimulation;
    int currentRound;

    // =============== Singleton ===============
    Client();
    Client(Client &);
    Client &operator=(Client &);
    ~Client();

public:
    static Client* instance();
    static bool GUIMode;


    // =================== MAIN FUNCTIONS ==============
    json runNextRound();
    void goToPreviousRound();
    void printRoundResults();
    void printUnit(const json &unit);
    // Main Client Function called by our "Embedded Hardware" Class, main.cpp
    void Run();

    std::vector<std::string> getCoutryUnits(std::string countryName);

    // Return a pair of country names that player 1 and player 2 choose
    // respectively
    std::pair<std::string, std::string> getPlayerCountries();

    void printHeader();

    void printFooter();

    // =================== GUI FUNCTIONS ==============

    json getAvailableSimulations();


    // =================== UTILITY FUNCTIONS ==============
public:
    std::string getListOfSimulations();
    void selectSimulation(int index);
    void runTerminalMode();
    void runGUIMode();

private:

    void loadSimulations(std::string filePath);

    void loadMobilization(const json& data);

    int getIntegerInput(std::string prompt, int rangeStart, int rangeEnd);

    bool isDigit(const std::string &str);

    int toInt(const std::string &str);

    void runSimulation();

    int getRoundCount(const json &data);
};

#endif  // CLIENT_H