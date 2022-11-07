#include "Client.h"

#include <limits.h>

#include <fstream>
#include <iostream>

#include "../utilities/WarException.h"

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

void Client::runDevMode() {
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
        json data = WarEngine::instance()->getOverallUnits();
        //std::cout<<data.dump(1)<<std::endl;
        displayUnits(data,stats["engine"]["day"]);
        WarEngine::instance()->loadBattleDayResults();
        printDayResults();
        
        std::cout << "Press any key to continue...";
        std::string input;
        std::cin >> input;
        std::cout << std::endl;
    }
}

void Client::displayUnits(const json &data, int day){
    std::cout<<"Would you like to tweak Day "<<day + 1<<"? (Yes/No)"<<std::endl;
    std::string input = "";
    std::cin >> input;
    std::cin.clear();
    input = toLower(input);
    if(input == "no" || input == "n") { return; }
    std::cout<<input;
    while(true){
        if(toLower(input) != "yes" && toLower(input) != "y" && toLower(input) != "n" && toLower(input) != "no"){
        std::cout<<"\033[1;31mInvalid Entry\033[0m"<<std::endl;
        std::cin >> input;
        std::cin.clear();
        }
        else if(toLower(input) == "n" || toLower(input) == "no"){
            return;
        }
        else{
            break;
        }
    }
    
    std::cout<<"\033[1;34m==================DEV MODE=====================\033[0m"<<std::endl;
    std::unordered_map<std::string,int> countries;
    std::vector<std::string> countries2;
    for(json country : data["data"]){
        countries[country["name"]] = 0;
        int counter = 1;
        countries2.push_back(country["name"]);
        std::cout<<country["name"].get<std::string>()<<": "<<std::endl;
        for(json unit : country["units"]){
            std::cout<<"\t"<<counter++<<". "<<unit["name"].get<std::string>()<<" - "<<unit["currentHP"].get<int>()<<"HP"<<std::endl;
            countries[country["name"].get<std::string>()]  = counter-1;
        }
    }
    std::vector<std::string> countries3 = countries2;
    for(int i = 0; i < countries3.size(); i++){
        countries3[i] = toLower(countries3[i]);
    }

    while(true){
        std::cout<<"\033[1;34mEnter the Country Name or 0 to continue with war: \033[0m";
        std::string countryName = "";
        
        std::cin >> countryName;
        std::cin.clear();
        if(countryName == "0"){
            break;
        }
        if (!(std::find(countries3.begin(), countries3.end(), toLower(countryName)) != countries3.end())){
            std::cout<<"\033[1;31mCountry does not exist\033[0m"<<std::endl;
        }
        else{
            std::string input = "";
            int pos = 0;
            while(true){
                std::cout<<"\033[1;34mEnter index of unit to move: \033[0m";
                std::cin >> input;
                std::cin.clear();
                std::stringstream ss(input);
                ss >> pos;
                // std::cout<<countryName<<std::endl;
                // std::cout<<countries[countryName]<<std::endl;
                if(pos > countries[countryName] || pos <= 0){
                    std::cout<<"\033[1;31mIndex does not exist\033[0m"<<std::endl;
                }
                else{
                    std::string type = "";
                    for(json country : data["data"]){
                        if(country["name"] == countryName){
                            type = country["units"][pos-1]["type"];
                            break;
                        }
                    }
                    std::string theatre = "";
                    Theatre * destination = NULL;
                    while(true){
                        std::cout<<"\033[1;34mEnter name of theatre where unit must be transported to: \033[0m";
                        std::cin >> theatre;
                        std::cin.clear();
                        destination = WarEngine::instance()->findTheatre(theatre);
                        if(!destination){
                            std::cout<<"\033[1;31mTheatre does not exist\033[0m"<<std::endl;
                        }
                        else{
                            int cnt = 0;
                            int cnt2 = 0;
                            for(json country : data["data"]){
                                if(country["name"].get<std::string>() == countryName){
                                    for(json unit : country["units"]){
                                        if(type == unit["type"].get<std::string>() && cnt2 != pos-1){
                                            cnt++;
                                        }
                                        else if(type == unit["type"].get<std::string>() && cnt2 == pos-1){
                                            break;
                                        }
                                        cnt2++;
                                    }
                                    break;
                                }
                            }
                            
                            try{
                                WarEngine::instance()->transportUnit(destination,countryName,type,cnt);
                            }
                            catch(WarException &e){
                                std::cout<<"\033[1;31m"<<e.getJSON().dump(1)<<std::endl;
                            }
                            break;
                        }
                    }
                }
                break;
            }
            
        }
    }
    std::cout<<"\033[1;34m===============================================\033[0m"<<std::endl;
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

std::string Client::toLower(std::string data){
    std::string d = data;
    for(int i = 0; i  <d.length();i++){
        d[i] = std::tolower(data[i]);
    }
    return d;
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