#include "WarEngine.h"
#include "../faction/Country.h"

#include <fstream>

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
    int counter = 1;
    for (int i = 0; i < theatreSize; i++) {
        theatres[i] = new Theatre*[theatreSize];
        for (int j = 0; j < theatreSize; j++) {
            
            theatres[i][j] = new Theatre("Theatre-" + std::to_string(counter), true);   //defaut all theatres sea for testing
            counter++;
        }
        
    } 
}

void WarEngine::loadSimulation(json& simulation) {
    generateFactions(simulation["factions"][0]["factionName"].get<std::string>(),simulation["factions"][1]["factionName"].get<std::string>());
    setsFactionBaseResoures(simulation["factions"][0]["baseResourceCount"].get<int>(),simulation["factions"][1]["baseResourceCount"].get<int>());
    setFaction1UnitNames(setToString((json)simulation["factions"][0]["names"]));
    setFaction2UnitNames(setToString((json)simulation["factions"][0]["names"]));
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

void WarEngine::generateFactions(std::string faction1, std::string faction2) {
    factions.push_back(new Country(faction1));
    factions.push_back(new Country(faction2));
}

void WarEngine::setsFactionBaseResoures(int faction1BaseCount, int faction2BaseCount){
    factions[0]->setBaseResourceCount(faction1BaseCount);
    factions[0]->generateResources();
    factions[1]->setBaseResourceCount(faction2BaseCount);
    factions[1]->generateResources();
}


// Think about output
void WarEngine::startSimulation(json war) {
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
            printMap();
            // std::cout<<"\033[1;32"<< 32 +
            // player<<"m======================================"<<std::endl;
            // std::cout<<std::endl;
            player1Turn = player1Turn ? false : true;
            std::cout<<std::endl;
        }

        // Phase 2
        chooseStrategies();
        //viewStrategies();
            
        

        // Phase 3
        CommenceBattle();
        CommenceBattle();
        CommenceBattle();
        printMap();

        // Switch Order of players taking turns for fairness
        player1Turn = player1Turn ? false : true;
        // To end while loop for testing
        warInProgress = false;
        // SAVE STATE HERE
        turnCounter++;
    }
}

void WarEngine::displayResources() {
    int resources =
        player1Turn ? factions[0]->getResourceCount() : factions[1]->getResourceCount();
    std::string factionName = player1Turn ? factions[0]->getName() : factions[1]->getName();
    std::cout << factionName << " Resources: " << resources << std::endl;
    //std::cout<<std::endl;
}

void WarEngine::buyUnits() {
    
    //displayUnitMenu();
    if(player1Turn){
        std::cout<<factions[0]->getName()<<" buying troops"<<std::endl;
        std::cout<<"Name: "<<faction1UnitNames["MediumAirUnit"]<<std::endl;

        ((Country *)factions[0])->addUnit(unitFactories["land"]->createHeavyUnit(faction1UnitNames["HeavyLandUnit"]));
        //((Country *)factions[0])->addUnit(unitFactories["land"]->createLightUnit(faction1UnitNames["LightLandUnit"]));
        //((Country *)factions[0])->addUnit(unitFactories["land"]->createLightUnit(faction1UnitNames["LightLandUnit"]));
        ((Country *)factions[0])->addUnit(unitFactories["air"]->createHeavyUnit(faction1UnitNames["HeavyAirUnit"]));
        //((Country *)factions[0])->addUnit(unitFactories["sea"]->createHeavyUnit(faction1UnitNames["HeavySeaUnit"]));
        //((Country *)factions[0])->addUnit(unitFactories["sea"]->createHeavyUnit(faction1UnitNames["HeavySeaUnit"]));
        ((Country *)factions[0])->addUnit(unitFactories["sea"]->createHeavyUnit(faction1UnitNames["HeavySeaUnit"]));
        std::cout<<std::endl;
    }
    else{
        std::cout<<factions[1]->getName()<<" buying troops"<<std::endl;
        // ((Country *)factions[1])->addUnit(unitFactories["land"]->createHeavyUnit(faction2UnitNames["HeavyLandUnit"]));
        // ((Country *)factions[1])->addUnit(unitFactories["land"]->createHeavyUnit(faction2UnitNames["HeavyLandUnit"]));
        // ((Country *)factions[1])->addUnit(unitFactories["land"]->createHeavyUnit(faction2UnitNames["HeavyLandUnit"]));
        // ((Country *)factions[1])->addUnit(unitFactories["land"]->createHeavyUnit(faction2UnitNames["HeavyLandUnit"]));
        // ((Country *)factions[1])->addUnit(unitFactories["air"]->createHeavyUnit(faction2UnitNames["HeavyAirUnit"]));
        // ((Country *)factions[1])->addUnit(unitFactories["air"]->createMediumUnit(faction2UnitNames["MediumAirUnit"]));
        // ((Country *)factions[1])->addUnit(unitFactories["sea"]->createHeavyUnit(faction2UnitNames["HeavySeaUnit"]));
        ((Country *)factions[1])->addUnit(unitFactories["land"]->createLightUnit(faction1UnitNames["LightLandUnit"]));
        
        ((Country *)factions[1])->addUnit(unitFactories["air"]->createLightUnit(faction1UnitNames["LightAirUnit"]));
       
        ((Country *)factions[1])->addUnit(unitFactories["sea"]->createLightUnit(faction1UnitNames["LightSeaUnit"]));
        std::cout<<std::endl;
    }
    //std::cout << "Enter Unit Type (Land, Sea, Air): ";
    //std::cout<<std::endl;
    
  
}

void WarEngine::displayUnits(){
    if(player1Turn){
        std::cout<<factions[0]->getName()<< " Troops:"<<std::endl;
        ((Country *)factions[0])->printUnits();
    }
    else{
        std::cout<<factions[1]->getName()<< " Troops:"<<std::endl;
        ((Country *)factions[1])->printUnits();
    }
}
/**
 * @brief Add 'parent' to unit to know which theatre its in
 *  Need to make function to remove unit from a theatre when its moved parent theatre pointer
 */

void WarEngine::placeTroops(){
    if(player1Turn){
        std::cout<<factions[0]->getName()<<" troop movements:"<<std::endl<<std::endl;
        std::vector<std::pair<int,int>> movements = {std::pair<int,int>(0,0),
                                                     std::pair<int,int>(1,1),
                                                     std::pair<int,int>(2,2)};
        int moveCount = 3; //I want to move 3 troops - random

        for(int k =0; k < moveCount;k++){
            std::cout<<((Country*) factions[0])->getUnit(k)->getName()<<" moving to "<<theatres[movements[k].first][movements[k].second]->getName()<<std::endl;
            theatres[movements[k].first][movements[k].second]->addEntity(factions[0]->getName(),((Country*) factions[0])->getUnit(k));
        }
    }
    else{
        std::cout<<factions[1]->getName()<<" troop movements:"<<std::endl<<std::endl;
        std::vector<std::pair<int,int>> movements = {std::pair<int,int>(0,0),
                                                     std::pair<int,int>(1,1),
                                                     std::pair<int,int>(2,2)};
        int moveCount = 3; //I want to move 3 troops - random

        for(int k =0; k < moveCount;k++){
            std::cout<<((Country*) factions[1])->getUnit(k)->getName()<<" moving to "<<theatres[movements[k].first][movements[k].second]->getName()<<std::endl;
            theatres[movements[k].first][movements[k].second]->addEntity(factions[1]->getName(),((Country*) factions[1])->getUnit(k));
        }
    }
}

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

/**
 * @brief 
 * Proposed JSON format:
 * "faction" : "factionName"
 * "strategyNumber" : "Strategy":TheatreRow,TheatreCol:"TargetFaction"
 * 
 * 
 * {
 *  "strategies" : [{
 *   "faction" : "Germany",
 *   "s1" : "Attack:0,0":"America",
 *   "s2" : "Defend:1,1":"America",
 *   "s3" : "Plan:2,2":"America",
 *  },
 *  {
 *   "faction" : "America",
 *   "s1" : "Attack:0,0":"Germany",
 *   "s2" : "Defend:1,1":"Germany",
 *   "s3" : "Plan:2,2":"Germany",
 *  }];
 * 
 */

/**
 * @brief Should be adjusted for multiple factions
 * 
 */




void WarEngine::chooseStrategies() {
    //set of strategies for each faction - vector for scalability
    std::vector<std::vector<WarStrategy*>> strategies = {{new AttackStrategy("America"), new CounterStrategy("America"), new PlanStrategy("America")},
                                                         {new PlanStrategy("Germany"), new AttackStrategy("Germany"), new CounterStrategy("Germany")}};

    std::vector<std::vector<std::pair<int,int>>> targets = {{std::pair<int,int>(0,0),std::pair<int,int>(1,1),std::pair<int,int>(2,2)},
                                                            {std::pair<int,int>(0,0),std::pair<int,int>(1,1),std::pair<int,int>(2,2)}};
    
    int factionCounter = 0;
    for(std::vector<std::pair<int,int>> list : targets){
        int strategyCounter = 0;
        for(std::pair<int,int> pair : list){
            if(theatres[pair.first][pair.second]->checkForFaction(factions[factionCounter]->getName())){
               
               theatres[pair.first][pair.second]->changeStrategy(factions[factionCounter]->getName(),strategies[factionCounter][strategyCounter]);
            }
            strategyCounter++;
        }
        factionCounter++;
    }
    
 
}

void WarEngine::CommenceBattle() {
    std::cout<<"Battle "<<turnCounter<<" commencing... "<<std::endl;
    
    for (int i = 0; i < theatreSize; i++) {
        for (int j = 0; j < theatreSize; j++) {
            theatres[i][j]->battle();
        }
    } 
    std::cout<<std::endl;
}

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
    std::cout<<"\033[0m=================MAP BEGIN================"<<std::endl;
    for (int i = 0; i < theatreSize; i++) {
        for (int j = 0; j < theatreSize; j++) {
            theatres[i][j]->printTheatre();
        }
    } 
    std::cout<<"=================MAP END================"<<std::endl;
    std::cout<<std::endl;
    
}

std::string WarEngine::toLower(std::string& str) const {
    std::string lower = "";

    for (int i = 0; i < str.length(); i++) {
        lower += tolower(str[i]);
    }

    return lower;
}



void WarEngine::viewStrategies(){
    std::cout<<"\033[1;32m=================TEST STRATS================="<<std::endl;
    for (int i = 0; i < theatreSize; i++) {
        for (int j = 0; j < theatreSize; j++) {
            theatres[i][j]->printStrategies();
        }
    } 
    std::cout<<"\033[1;32m============================================="<<std::endl;
}

std::vector<std::string> WarEngine::setToString(json array){
    std::vector<std::string> str;
    for(std::string name : array){
       str.push_back(name);
    }
    return str;
}

// int WarEngine::setToInteger(std::string data){
//     std::stringstream ss(setToString(data));
//     int num = 0;
//     ss >> num;
//     return num;
// }

