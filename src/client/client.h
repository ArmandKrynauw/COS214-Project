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
    json chosenSimulation;
    int currentRound;

public:
    static Client* instance();
    void runTerminalMode();
    void runGUIMode();

    // =================== WAR ENGINE CONTROL FUNCTIONS ===================
    json loadNextRound();
    json loadRoundResults();
    json loadPreviousRound();
    json selectSimulation(int index);

    // Depreciated!! Needs to be merged into loadNextRound
    // Ask Armand before removing
    json runNextRound();

    // =================== JSON UTILITY FUNCTIONS ===================

    /**
     * Returns a JSON array of strings. Each string is a name of a war
     * simulation.
     *
     * @return Array of war simulation names
    */
    json getAvailableSimulations();

private:
    // =============== Singleton ===============
    Client();
    Client(Client &);
    Client &operator=(Client &);
    ~Client();

    // =================== TERMINAL MODE FUNCTIONS ===================
    void runSimulation();
    void printRoundResults();
    void printUnit(const json &unit);

    // =================== GUI MODE FUNCTIONS ==============


    // =================== UTILITY FUNCTIONS ===================
    void loadSimulations(std::string filePath);

    // =================== SMALL UTILITY FUNCTIONS ===================
    int getIntegerInput(std::string prompt, int rangeStart, int rangeEnd);
    bool isDigit(const std::string &str);
    int toInt(const std::string &str);
};

#endif  // CLIENT_H