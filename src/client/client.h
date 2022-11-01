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
    bool GUIMode;
    std::map<std::string, std::vector<std::string> > countries;
    WarSocket *socket;
    std::vector<std::string> availableCountries;
    json chosenSimulation;
    int currentRound;

public:
    Client(bool GUIMode);

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

    // =================== UTILITY FUNCTIONS ==============
public:
    std::string getListOfSimulations();
    void selectSimulation(int index);

private:
    void runTerminalMode();

    void runGUIMode();

    void loadSimulations(std::string filePath);

    int getIntegerInput(std::string prompt, int rangeStart, int rangeEnd);

    bool isDigit(const std::string &str);

    int toInt(const std::string &str);

    void runSimulation();

    int getRoundCount(const json &data);
};

#endif  // CLIENT_H