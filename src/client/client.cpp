#include "client.h"

#include <limits.h>

#include <fstream>
#include <iostream>

Client::Client(bool GUIMode) : GUIMode(GUIMode) {
    try {
        loadSimulations("utilities/simulations.json");

        if (GUIMode) {
            runGUIMode();
        } else {
            runTerminalMode();
        }
    } catch (WarException &e) {
        std::cout << e.what() << std::endl;
    }
}

void Client::runTerminalMode() {
    std::cout << "\033[1;32m==============SELECT SIMULATION===========\033[0m"
              << std::endl;
    for (int i = 0; i < simulations.size(); i++) {
        std::cout << i + 1 << ". "
                  << simulations[i]["WarTitle"].get<std::string>() << std::endl;
    }
    std::cout << std::endl;
    int choice =
            getIntegerInput("Select a simulation", 1, simulations.size()) - 1;
    selectSimulation(choice);
    WarEngine::instance()->purchaseUnits(
            simulations[choice]["rounds"][0]["unitsToPurchase"]);

    std::cout << WarEngine::instance()->getCountryUnits().dump() << std::endl;
}

void Client::runGUIMode() {
    //this->socket = new WarSocket();
    std::cout << "\033[1;32m==============SELECT SIMULATION===========\033[0m"
              << std::endl;
    for (int i = 0; i < simulations.size(); i++) {
        std::cout << i + 1 << ". "
                  << simulations[i]["WarTitle"].get<std::string>() << std::endl;
    }
    std::cout << std::endl;
    int choice =
            getIntegerInput("Select a simulation", 1, simulations.size()) - 1;
    selectSimulation(choice);

    runSimulation();
    // WarEngine::instance()->purchaseUnits(
    //     simulations[choice]["rounds"][0]["unitsToPurchase"]);

    //this->socket->listen();
}

void Client::runSimulation() {
    int end = getRoundCount(chosenSimulation["rounds"]);
    int roundCnt = 0;
    for (json roundData: chosenSimulation["rounds"][roundCnt]) {
        if (roundCnt != end) {
            WarEngine::instance()->checkEscalation(chosenSimulation["rounds"][roundCnt]["WarState"]);
            WarEngine::instance()->purchaseUnits(
                    chosenSimulation["rounds"][roundCnt]["unitsToPurchase"]);
            // std::cout << WarEngine::instance()->getCountryUnits().dump(2) << std::endl;
            WarEngine::instance()->relocateUnits(
                    chosenSimulation["rounds"][roundCnt]["unitsToRelocate"]);
            WarEngine::instance()->assignStrategies(
                    chosenSimulation["rounds"][roundCnt]["strategies"]
            );
            WarEngine::instance()->CommenceBattle();
            //WarEngine::instance()->printMap();
            WarEngine::instance()->printBattleResults();
            roundCnt++;

            std::cout << "Press any key to continue...";
            std::string input;
            std::cin >> input;
            std::cout << std::endl;
        }
    }
}

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

std::string Client::getListOfSimulations() {
    std::vector<std::string> names;

    for (int i = 0; i < simulations.size(); i++) {
        names.push_back(simulations[i]["WarTitle"].get<std::string>());
    }

    json data(names);
    return data.dump();
}

void Client::selectSimulation(int index) {
    if (index < 0 || index >= simulations.size()) {
        throw WarException("out-of-bounds");
    }

    WarEngine::instance()->loadSimulation(simulations[index]);
    chosenSimulation = simulations[index];
}

int Client::getRoundCount(const json &data) {
    int max = 0;
    for (json round: data) {
        if (round["turnNumber"].get<int>() > max) {
            max++;
        }
    }
    return max;
}

// void Client::Run(){
//     std::cout<<"\033[1;32m================== CLIENT BOOTUP
//     =================="<<std::endl; std::cout<<std::endl;

//     //Different Country Unit Names
//     availableCountries.push_back("Germany");
//     // std::vector<std::string> germany{"Foot Soldier","BMP-3","Leopard 2A7",
//     //                                  "Baden-Württemberg
//     class","Braunschweig class","Type 212 Submarine",
//     //                                  "CH-53G","Eurofighter
//     Typhoon","Luftwaffe A400M"};

//     std::vector<std::string> germany{"Luftwaffe A400M","Leopard 2A7","Type
//     212 Submarine",
//                                      "CH-53G","Foot
//                                      Soldier","Baden-Württemberg class",
//                                      "Eurofighter
//                                      Typhoon","BMP-3","Braunschweig class"};

//     countries.insert(std::pair<std::string,std::vector<std::string>>("Germany",germany));

//     availableCountries.push_back("America");
//     // std::vector<std::string> america{"Foot Soldier","HMMWV","M1 Abrams",
//     //                                  "Cruiser","Destroyer","USS Nebraska
//     (SSBN-739)",
//     //                                  "F-22A Raptors","A-10","C-17"};

//     std::vector<std::string> america{"C-17","M1 Abrams","USS Nebraska
//     (SSBN-739)",
//                                      "F-22A Raptors","Foot
//                                      Soldier","Cruiser",
//                                     "A-10","HMMWV","Destroyer"};

//     countries.insert(std::pair<std::string,std::vector<std::string>>("America",america));

//     /**Assign Country for each side of the simulation*/
//     std::pair<std::string,std::string> choices = getPlayerCountries();
//     //std::cout<<"here"<<std::endl;
//     WarEngine::instance()->setFaction1UnitNames(countries[choices.first]);
//     WarEngine::instance()->setFaction2UnitNames(countries[choices.second]);
//     //std::cout<<"here"<<std::endl;

//     WarEngine::instance()->setCountryNames(choices);
//     //std::cout<<"here"<<std::endl;

//     WarEngine::instance()->setsFactionBaseResoures(350,400);

//     std::cout<<"War to take place: "<<choices.first<< " Vs "
//     <<choices.second<<std::endl; std::cout<<std::endl; printHeader();
//    WarEngine::instance()->startSimulation();

//     printFooter();
// }

// std::pair<std::string,std::string> Client::getPlayerCountries(){
//     std::cout<<"Available countries: "<<std::endl;
//     std::string str = "";
//     for(std::pair<std::string,std::vector<std::string>> pair : countries){
//         str = str + pair.first + ", ";
//     }
//     str = str.substr(0,str.length()-2);
//     std::cout<<str<<std::endl;
//     std::cout<<std::endl;

//     std::pair<std::string,std::string> inputs;
//     // std::cout<<"\033[1;33mPlayer 1 -> Enter name of country you woud like
//     to play: ";
//     // std::cin >> inputs.first;
//     // std::cout<<std::endl;
//     // std::cout<<"\033[1;34mPlayer 2 -> Enter name of country you woud like
//     to play: ";
//     // std::cin >> inputs.second;
//     // std::cout<<std::endl;

//     inputs.first = "Germany";
//     inputs.second = "America";
//     return inputs;
// }

// void Client::printHeader(){
//     std::cout<<"\033[1;32m=============== START OF SIMULATION
//     ===============\033[0m"<<std::endl; std::cout<<std::endl;
// }

// void Client::printFooter(){
//     std::cout<<std::endl;
//     std::cout<<"\033[1;32m================= END OF SIMULATION
//     =================\033[0m"<<std::endl;

// }

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