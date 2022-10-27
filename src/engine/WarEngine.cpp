#include "WarEngine.h"

#include "../faction/Country.h"

WarEngine* WarEngine::instance() {
    static WarEngine warEngine;     
    return &warEngine;
}

WarEngine::WarEngine() {
    addNames();
    unitFactories["land"] = new LandUnitFactory();
    unitFactories["sea"] = new SeaUnitFactory();
    unitFactories["air"] = new AirUnitFactory();

    theatreSize = 3;
    theatres = new Theatre**[theatreSize];
    for (int i = 0; i < theatreSize; i++) {
        theatres[i] = new Theatre*[theatreSize];
        for (int j = 0; j < theatreSize; j++) {
            theatres[i][j] = new Theatre("Theatre-" + std::to_string(i+j+1), false);
        }
    } 
}

void WarEngine::setFaction1UnitNames(std::vector<std::string> names) {
    int counter = 0;
    for (it = faction1UnitNames.begin(); it != faction1UnitNames.end(); ++it) {
        it->second = names[counter];
        counter++;
    }
}

void WarEngine::setFaction2UnitNames(std::vector<std::string> names) {
    int counter = 0;
    for (it = faction2UnitNames.begin(); it != faction2UnitNames.end(); ++it) {
        it->second = names[counter];
        counter++;
    }
}

void WarEngine::setCountryNames(std::pair<std::string, std::string> names) {
    faction1 = new Country(names.first);
    faction2 = new Country(names.second);
}

void WarEngine::setsFactionBaseResoures(int faction1BaseCount, int faction2BaseCount){
    
    faction1->setBaseResourceCount(faction1BaseCount);
    faction1->generateResources();
    faction2->setBaseResourceCount(faction2BaseCount);
    faction2->generateResources();
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
            std::cout << "\033[1;" << 32 + player << "mFaction: " << player <<std::endl
                      << "Turn: " << turnCounter
                      <<  std::endl;
            displayResources();
            buyUnits();
            displayUnits();
            placeTroops();
            // std::cout<<"\033[1;32"<< 32 +
            // player<<"m======================================"<<std::endl;
            // std::cout<<std::endl;
            player1Turn = player1Turn ? false : true;
            std::cout<<std::endl;
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
        // SAVE STATE HERE
    }
}

void WarEngine::displayResources() {
    int resources =
        player1Turn ? faction1->getResourceCount() : faction2->getResourceCount();
    std::string factionName = player1Turn ? faction1->getName() : faction2->getName();
    std::cout << factionName << " Resources: " << resources << std::endl;
    //std::cout<<std::endl;
}

void WarEngine::buyUnits() {
    
    //displayUnitMenu();
    if(player1Turn){
        std::cout<<faction1->getName()<<" buying troops"<<std::endl;
        ((Country *)faction1)->addUnit(unitFactories["land"]->createHeavyUnit(faction1UnitNames["HeavyLandUnit"]));
        ((Country *)faction1)->addUnit(unitFactories["air"]->createHeavyUnit(faction1UnitNames["HeavyAirUnit"]));
        ((Country *)faction1)->addUnit(unitFactories["sea"]->createHeavyUnit(faction1UnitNames["HeavySeaUnit"]));
    }
    else{
        std::cout<<faction2->getName()<<" buying troops"<<std::endl;
        ((Country *)faction2)->addUnit(unitFactories["land"]->createHeavyUnit(faction2UnitNames["HeavyLandUnit"]));
        ((Country *)faction2)->addUnit(unitFactories["air"]->createHeavyUnit(faction2UnitNames["HeavyAirUnit"]));
        ((Country *)faction2)->addUnit(unitFactories["sea"]->createHeavyUnit(faction2UnitNames["HeavySeaUnit"]));
    }
    //std::cout << "Enter Unit Type (Land, Sea, Air): ";
    //std::cout<<std::endl;
    
  
}

void WarEngine::displayUnits(){
    if(player1Turn){
        ((Country *)faction1)->printUnits();
    }
    else{
        ((Country *)faction2)->printUnits();
    }
}

void WarEngine::placeTroops(){
    if(player1Turn){
        std::cout<<faction1->getName()<<" placing troops"<<std::endl;
    }
    else{
        std::cout<<faction2->getName()<<" placing troops"<<std::endl;
    }
}


// List of Available Units
    //      Land:
    //          1. Trooper
    //          2. Troop
    //      Sea:
    //      Air:
void WarEngine::displayUnitMenu(){
    std::cout<<"List of Available Units"<<std::endl;
    if(player1Turn)
    {
          int counter = 1;
          for (it = faction1UnitNames.begin(); it != faction1UnitNames.end(); ++it) {
                if(counter == 1){
                    std::cout<<"Land:"<<std::endl;
                }
                else if(counter == 4){
                    std::cout<<"Sea:"<<std::endl;
                }
                else if(counter == 7){
                    std::cout<<"Air:"<<std::endl;
                }
                std::cout <<"\t"<<counter<<". "<< it->second<<std::endl;
                counter++;
           }
    }
    else{
        int counter = 1;
          for (it = faction2UnitNames.begin(); it != faction2UnitNames.end(); ++it) {
                if(counter == 1){
                    std::cout<<"Land:"<<std::endl;
                }
                else if(counter == 4){
                    std::cout<<"Sea:"<<std::endl;
                }
                else if(counter == 7){
                    std::cout<<"Air:"<<std::endl;
                }
                std::cout <<"\t"<< counter<<". "<< it->second<<std::endl;
                counter++;
           }
    }
    std::cout<<std::endl;
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





void WarEngine::chooseStrategies() {
    if (player1Turn) {
        faction1->chooseStrategy();
    } else {
        faction2->chooseStrategy();
    }
}

void WarEngine::CommenceBattle() {}

WarEngine::~WarEngine() {
    for (int i = 0; i < theatreSize; i++) {
        for (int j = 0; j < theatreSize; j++) {
            delete theatres[i][j];
        }
        delete [] theatres[i];
    }
    delete theatres;

    std::unordered_map<std::string, UnitFactory*>::iterator it;
    for (it = unitFactories.begin(); it != unitFactories.end(); it++) {
        delete it->second;
    }
}


// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

void WarEngine::addNames() {
    faction1UnitNames.insert(
        std::pair<std::string, std::string>("LightLandUnit", ""));
    faction1UnitNames.insert(
        std::pair<std::string, std::string>("MediumLandUnit", ""));
    faction1UnitNames.insert(
        std::pair<std::string, std::string>("HeavyLandUnit", ""));

    faction1UnitNames.insert(
        std::pair<std::string, std::string>("LightSeaUnit", ""));
    faction1UnitNames.insert(
        std::pair<std::string, std::string>("MediumSeaUnit", ""));
    faction1UnitNames.insert(
        std::pair<std::string, std::string>("HeavySeaUnit", ""));

    faction1UnitNames.insert(
        std::pair<std::string, std::string>("LightAirUnit", ""));
    faction1UnitNames.insert(
        std::pair<std::string, std::string>("MediumAirUnit", ""));
    faction1UnitNames.insert(
        std::pair<std::string, std::string>("HeavyAirUnit", ""));

    faction2UnitNames.insert(
        std::pair<std::string, std::string>("LightLandUnit", ""));
    faction2UnitNames.insert(
        std::pair<std::string, std::string>("MediumLandUnit", ""));
    faction2UnitNames.insert(
        std::pair<std::string, std::string>("HeavyLandUnit", ""));

    faction2UnitNames.insert(
        std::pair<std::string, std::string>("LightSeaUnit", ""));
    faction2UnitNames.insert(
        std::pair<std::string, std::string>("MediumSeaUnit", ""));
    faction2UnitNames.insert(
        std::pair<std::string, std::string>("HeavySeaUnit", ""));

    faction2UnitNames.insert(
        std::pair<std::string, std::string>("LightAirUnit", ""));
    faction2UnitNames.insert(
        std::pair<std::string, std::string>("MediumAirUnit", ""));
    faction2UnitNames.insert(
        std::pair<std::string, std::string>("HeavyAirUnit", ""));
}

void WarEngine::printMap() {
    
}

std::string WarEngine::toLower(std::string& str) const {
    std::string lower = "";

    for (int i = 0; i < str.length(); i++) {
        lower += tolower(str[i]);
    }

    return lower;
}