#include "client.h"

#include <limits.h>

#include <fstream>
#include <iostream>

Client::Client() {
    try {
        loadSimulations("utilities/simulations.json");
    } catch (WarException &e) {
        std::cout << e.what() << std::endl;
    }
}

Client* Client::instance() {
    static Client client;
    return &client;
}

void Client::runTerminalMode() {
    std::cout << "\033[1;32m==============SELECT SIMULATION===========\033[0m" << std::endl;
    for (int i = 0; i < simulations.size(); i++) {
        std::cout << i + 1 << ". " << simulations[i]["WarTitle"].get<std::string>() << std::endl;
    }
    std::cout << std::endl;
    int choice = getIntegerInput("Select a simulation", 1, simulations.size()) - 1;
    selectSimulation(choice);
    std::cout << std::endl;
    runSimulation();
}

void Client::runGUIMode() {
    selectSimulation(0);
    // WarEngine::instance()->checkEscalation(chosenSimulation["rounds"][0]["WarState"]);
    // WarEngine::instance()->purchaseUnits(chosenSimulation["rounds"][0]["unitsToPurchase"]);
}

// ======================================================================================
// WAR ENGINE CONTROL FUNCTIONS
// ======================================================================================

json Client::loadNextRound() {
    std::ifstream file("utilities/data.json");
    if (!file) {
        throw WarException("file-not-found");
    }
    return json::parse(file);
}

json Client::loadRoundResults() {
    std::ifstream file("utilities/data.json");
    if (!file) {
        throw WarException("file-not-found");
    }
    return json::parse(file);
}

json Client::loadPreviousRound() {
    std::ifstream file("utilities/data.json");
    if (!file) {
        throw WarException("file-not-found");
    }
    return json::parse(file);
}

json Client::selectSimulation(int index) {
    if (index < 0 || index >= simulations.size()) {
        throw WarException("out-of-bounds");
    }

    WarEngine::instance()->loadSimulation(simulations[index]);
    WarEngine::instance()->loadTheatres(simulations[index]["theatres"]);
    chosenSimulation = simulations[index];

    // Don't ask why
    return loadPreviousRound();
}

// Depreciated
json Client::runNextRound() {
        WarEngine::instance()->checkMobilization(chosenSimulation["rounds"][currentRound]["mobilization"]);
        WarEngine::instance()->checkEscalation(chosenSimulation["rounds"][currentRound]["WarState"]);
        WarEngine::instance()->generateCountryResources(chosenSimulation["countries"],chosenSimulation["alliances"]);
        WarEngine::instance()->purchaseUnits(chosenSimulation["rounds"][currentRound]["unitsToPurchase"]);
        WarEngine::instance()->relocateUnits(chosenSimulation["rounds"][currentRound]["unitsToRelocate"]);
        // std::cout<<WarEngine::instance()->getStats().dump(8)<<std::endl;

        WarEngine::instance()->assignStrategies(chosenSimulation["rounds"][currentRound]["strategies"]);
        WarEngine::instance()->CommenceBattle();
        currentRound++;
        return WarEngine::instance()->getRoundResults();
}

// ======================================================================================
// JSON UTILITY FUNCTIONS
// ======================================================================================

json Client::getAvailableSimulations() {
    json data;

    for (json s : simulations) {
        json j = json{
            { "name", s["WarTitle"] },
            { "countries", json::array() },
            { "alliances", json::array() }
        };

        for (json c : s["countries"]) {
            j["countries"].push_back({
                { "name", c["name"] },
                { "countryCode", c["countryCode"] },
            });
        }

        for (json a : s["alliances"]) {
            j["alliances"].push_back(a);
        }

        data.push_back(j);
    }

    return data;
}

// ======================================================================================
// TERMINAL MODE FUNCTIONS
// ======================================================================================

void Client::runSimulation() {
    currentRound = 0;
    int end = chosenSimulation["duration"];
    for (json roundData: chosenSimulation["rounds"][currentRound]) {
        if (currentRound != end) {
            std::cout << "Battle " << currentRound + 1 << " commencing... " << std::endl;
            json result = runNextRound();
            json deaths = result["casualities"];
            printRoundResults();
            // std::cout << WarEngine::instance()->getTheatreUnits().dump(2) << std::endl;
            // WarEngine::instance()->getTheatreUnits();
            // std::cout << WarEngine::instance()->clearCasualties().dump(2) << std::endl;
            //  WarEngine::instance()->clearCasualties();
            //pass data to GUI
            std::cout << "Press any key to continue...";
            std::string input;
            std::cin >> input;
            std::cout << std::endl;
        }
    }
}

void Client::printRoundResults() {
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
// GUI MODE FUNCTIONS
// ======================================================================================


// ======================================================================================
// UTILITY FUNCTIONS
// ======================================================================================

void Client::loadSimulations(std::string filePath) {
    std::ifstream file(filePath);

    if (!file) {
        throw WarException("file-not-found");
    }

    json data = json::parse(file);

    for (json simulation: data["Wars"]) {
        simulations.push_back(simulation);
    }
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