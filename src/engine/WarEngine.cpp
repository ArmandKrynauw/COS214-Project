#include "WarEngine.h"

#include "../faction/Country.h"

WarEngine::WarEngine() {
    // Jake's works :)
    addNames();

    unitFactories["land"] = new LandUnitFactory();
    unitFactories["sea"] = new SeaUnitFactory();
    unitFactories["air"] = new AirUnitFactory();
}

void WarEngine::setPlayer1UnitNames(std::vector<std::string> names) {
    int counter = 0;
    for (it = player1UnitNames.begin(); it != player1UnitNames.end(); ++it) {
        it->second = names[0];
        counter++;
    }
}

void WarEngine::setPlayer2UnitNames(std::vector<std::string> names) {
    int counter = 0;
    for (it = player2UnitNames.begin(); it != player2UnitNames.end(); ++it) {
        it->second = names[0];
        counter++;
    }
}

void WarEngine::setCountryNames(std::pair<std::string, std::string> names) {
    player1 = new Country(names.first);
    player2 = new Country(names.second);
}

// Think about output
void WarEngine::startSimulation() {
    turnCounter = 1;
    player1Turn = true;
    bool warInProgress = true;

    // Round
    while (warInProgress) {
        // Phase 1
        for (int i = 0; i < 2; i++) {
            int player = player1Turn ? 1 : 2;
            std::cout << "\033[1;" << 32 + player << "mPlayer: " << player
                      << " Turn: " << turnCounter
                      << " ====================" << std::endl;
            displayResources();
            // buyUnits();
            // PlaceTroops();
            // std::cout<<"\033[1;32"<< 32 +
            // player<<"m======================================"<<std::endl;
            // std::cout<<std::endl;
            player1Turn = player1Turn ? false : true;
        }

        // Phase 2
        for (int i = 0; i < 2; i++) {
            chooseStrategies();
            player1Turn = player1Turn ? false : true;
        }

        // Phase 3
        CommenceBattle();

        // Switch Order of players taking turns for fairness
        player1Turn = player1Turn ? false : true;
        // To end while loop for testing
        warInProgress = false;
    }
}

void WarEngine::displayResources() {
    int resources =
        player1Turn ? player1->getResourceCount() : player2->getResourceCount();
    std::cout << "Your Resources: " << resources << std::endl;
}

void WarEngine::buyUnits(Country* country) {
    
    // List of Available Units
    //      Land:
    //          1. Trooper
    //          2. Troop
    //      Sea:
    //      Air:
    displayUnitMenu();

    std::cout << "Enter Unit Type (Land, Sea, Air): ";

    
    

    
}

// bool slab() {
// 	string choice;
// 	cout << "\nWant a slab? (Y/N) ";
// 	cin >> choice;
// 	while (!(choice == "y" || choice == "Y" ||choice == "n" || choice == "N")) {
// 		cin.clear();
// 		cin.ignore(INT_MAX, '\n');
// 		cout << "\033[1;31mPick Y/N: \033[0m";
// 		cin >> choice;
// 	}
// 	return choice == "Y" || choice == "y";
//}



/**
 * Limited amount of strategies per faction round.
 *
 *
 * Attack Strategy (default strategy in sense): Sum all attack power and just
 * attack as normal.
 *
 *
 * Plan Strategy: Skip turn, next turn in theatre attacks stats will be boosted.
 * If one side plan and other side attacks, normal attack. If other guy predict
 * attack and counters then you lose stats.
 *
 * Counter Strategy:
 *
 *
 *
 * How attack will work:
 * Sum attack of your side
 *
 * War is not is not deterministic, need RNG. Sum faction attack power (each
 * units damage value). Count amount of enemies on enemy side. Divide attack
 * power by amount of enemies. Randomly attack enemy side troops.
 *
 *
 * Amount of attacks/strategies needs to be scalable. e.g. 5 theatres, 3 attacks
 * per side. Can't attack all at once.
 *
 *
 *
 * How to win:
 *
 *
 *
 *
 *
 */

void WarEngine::displayUnitMenu(){
    std::cout<<"==MENU=="<<std::endl;
    if(player1Turn)
    {
          int counter = 1;
          for (it = player1UnitNames.begin(); it != player1UnitNames.end(); ++it) {
                if(counter == 1){
                    std::cout<<"==Land=="<<std::endl;
                }
                else if(counter == 4){
                    std::cout<<"==Sea=="<<std::endl;
                }
                else if(counter == 7){
                    std::cout<<"==Air"<<std::endl;
                }
                cout << counter<<". " << it->first <<": " << it->second<<std::endl;
                counter++;
           }
    }
    else{
        int counter = 1;
          for (it = player2UnitNames.begin(); it != player2UnitNames.end(); ++it) {
                if(counter == 1){
                    std::cout<<"==Land=="<<std::endl;
                }
                else if(counter == 4){
                    std::cout<<"==Sea=="<<std::endl;
                }
                else if(counter == 7){
                    std::cout<<"==Air"<<std::endl;
                }
                cout << counter<<". " << it->first <<": " << it->second<<std::endl;
                counter++;
           }
    }
}



void WarEngine::chooseStrategies() {
    if (player1Turn) {
        player1->chooseStrategy();
    } else {
        player2->chooseStrategy();
    }
}

void WarEngine::CommenceBattle() {}

WarEngine::~WarEngine() {}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

void WarEngine::addNames() {
    player1UnitNames.insert(
        std::pair<std::string, std::string>("LightLandUnit", ""));
    player1UnitNames.insert(
        std::pair<std::string, std::string>("MediumLandUnit", ""));
    player1UnitNames.insert(
        std::pair<std::string, std::string>("HeavyLandUnit", ""));

    player1UnitNames.insert(
        std::pair<std::string, std::string>("LightSeaUnit", ""));
    player1UnitNames.insert(
        std::pair<std::string, std::string>("MediumSeaUnit", ""));
    player1UnitNames.insert(
        std::pair<std::string, std::string>("HeavySeaUnit", ""));

    player1UnitNames.insert(
        std::pair<std::string, std::string>("LightAirUnit", ""));
    player1UnitNames.insert(
        std::pair<std::string, std::string>("MediumAirUnit", ""));
    player1UnitNames.insert(
        std::pair<std::string, std::string>("HeavyAirUnit", ""));

    player2UnitNames.insert(
        std::pair<std::string, std::string>("LightLandUnit", ""));
    player2UnitNames.insert(
        std::pair<std::string, std::string>("MediumLandUnit", ""));
    player2UnitNames.insert(
        std::pair<std::string, std::string>("HeavyLandUnit", ""));

    player2UnitNames.insert(
        std::pair<std::string, std::string>("LightSeaUnit", ""));
    player2UnitNames.insert(
        std::pair<std::string, std::string>("MediumSeaUnit", ""));
    player2UnitNames.insert(
        std::pair<std::string, std::string>("HeavySeaUnit", ""));

    player2UnitNames.insert(
        std::pair<std::string, std::string>("LightAirUnit", ""));
    player2UnitNames.insert(
        std::pair<std::string, std::string>("MediumAirUnit", ""));
    player2UnitNames.insert(
        std::pair<std::string, std::string>("HeavyAirUnit", ""));
}

std::string WarEngine::toLower(std::string& str) const {
    std::string lower = "";

    for (int i = 0; i < str.length(); i++) {
        lower += tolower(str[i]);
    }

    return lower;
}