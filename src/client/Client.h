#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <iterator>
#include <map>
#include <vector>

#include "WarSocket.h"

using json = nlohmann::json;

class Client {
public:
    static Client* instance();
    void runDevMode();
    void runTest();

private:
    // =============== Singleton ===============
    Client();
    Client(Client &);
    Client &operator=(Client &);
    ~Client();

    // =================== TERMINAL MODE FUNCTIONS ===================
    void runSimulation();
    void printDayResults();
    void printUnit(const json &unit);
    void displayUnits(const json &data, int day);
    
    // =================== UTILITY FUNCTIONS ===================
    void loadSimulations(std::string filePath);

    // =================== SMALL UTILITY FUNCTIONS ===================
    int getIntegerInput(std::string prompt, int rangeStart, int rangeEnd);
    bool isDigit(const std::string &str);
    int toInt(const std::string &str);
    std::string toLower(std::string data);
};

#endif  // CLIENT_H