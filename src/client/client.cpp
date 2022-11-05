#include "client.h"

#include <limits.h>

#include <fstream>
#include <iostream>

Client::Client() { }

Client* Client::instance() {
    static Client client;
    return &client;
}

void Client::runTest() {
    WarEngine::instance()->selectSimulation(0);
    WarEngine::instance()->loadNextBattleDay();
}

// ======================================================================================
// TERMINAL MODE FUNCTIONS
// ======================================================================================

void Client::runTerminalMode() {
    std::cout << "\033[1;32m==============SELECT SIMULATION===========\033[0m" << std::endl;
    json simulations = WarEngine::instance()->getAvailableSimulations();
    for (int i = 0; i < simulations.size(); i++) {
        std::cout << i + 1 << ". " << simulations[i]["name"].get<std::string>() << std::endl;
    }
    std::cout << std::endl;
    int choice = getIntegerInput("Select a simulation", 1, simulations.size()) - 1;
    WarEngine::instance()->selectSimulation(choice);
    std::cout << std::endl;
    runSimulation();
}

void Client::runSimulation() {
    // std::cout<<WarEngine::instance()->getStats().dump(4)<<std::endl;

    json stats = WarEngine::instance()->getStats();
    while (stats["engine"]["day"].get<int>() != stats["engine"]["duration"].get<int>() - 1) {
        stats = WarEngine::instance()->getStats();
        std::cout << "Day " << stats["engine"]["day"].get<int>() + 1 << " commencing... " << std::endl;
        //json deaths = result["casualties"];
        WarEngine::instance()->loadNextBattleDay();
        // std::cout<<WarEngine::instance()->getStats().dump(4)<<std::endl;
        WarEngine::instance()->loadBattleDayResults();
        printDayResults();
        //std::cout << WarEngine::instance()->clearCasualties().dump(1) << std::endl;
        // WarEngine::instance()->clearCasualties();
        // std::cout << WarEngine::instance()->clearCasualties().dump(2) << std::endl;
        //  WarEngine::instance()->clearCasualties();
        //pass data to GUI
        std::cout << "Press any key to continue...";
        std::string input;
        std::cin >> input;
        std::cout << std::endl;
    }
}

void Client::printDayResults() {
    //Remove Casualties 
    std::cout << "=====================BATTLE RESULTS=====================" << std::endl;
    json data = WarEngine::instance()->getTheatreUnits();
    for (json country: data) {
        std::cout << country["name"].get<std::string>() << ": " << std::endl;
        for (json theatre: country["theatres"]) {
            std::cout << "\t" << theatre["name"].get<std::string>() << ": " << std::endl;
            for (json unit: theatre["units"]) {
                printUnit(unit);
            }
        }
    }
    std::cout << "========================================================" << std::endl;
}

void Client::printUnit(const json &unit) {
    std::cout << "\t\t" << "Name: " << unit["name"].get<std::string>() << " Type: " << unit["type"].get<std::string>()
              << " Current HP: " << unit["currentHP"] << std::endl;
}

// ======================================================================================
// SMALL UTILITY FUNCTIONS
// ======================================================================================

int Client::getIntegerInput(std::string prompt, int rangeStart, int rangeEnd) {
    int choice;
    std::string line;
    std::cout << prompt << ": ";
    std::getline(std::cin, line);

    while (!isDigit(line) || toInt(line) < rangeStart ||
           toInt(line) > rangeEnd) {
        std::cout << "\033[1;31mPick a number [" << rangeStart << "-"
                  << rangeEnd << "]: \033[0m";
        std::getline(std::cin, line);
    }

    return toInt(line);
}

bool Client::isDigit(const std::string &str) {
    for (int i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

int Client::toInt(const std::string &str) {
    std::stringstream ss;
    ss << str;
    int val;
    ss >> val;
    return val;
}

Client::~Client() {}