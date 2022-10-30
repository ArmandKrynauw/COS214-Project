#include "WarEngine.h"

#include <fstream>

#include "../faction/Country.h"

WarEngine* WarEngine::instance() {
    static WarEngine warEngine;
    return &warEngine;
}

WarEngine::WarEngine() {
    srand(1);

    unitFactories["land"] = new LandUnitFactory();
    unitFactories["sea"] = new SeaUnitFactory();
    unitFactories["air"] = new AirUnitFactory();

    theatreSize = 3;
    theatres = new Theatre**[theatreSize];
    int counter = 1;
    for(int i = 0; i < theatreSize; i++) {
        theatres[i] = new Theatre*[theatreSize];
        for(int j = 0; j < theatreSize; j++) {
            theatres[i][j] =
                new Theatre("Theatre-" + std::to_string(counter),
                            true);  // defaut all theatres sea for testing
            counter++;
        }
    }
}

void WarEngine::loadSimulation(const json& simulation) {
    if(!simulation.contains("countries")) {
        throw WarException("Malformed JSON object, countries not found.",
                           "malformed_countries");
    }

    loadCountries(simulation["countries"]);

    if(simulation.contains("alliances")) {
        loadAlliances(simulation["alliances"]);
    }
}

void WarEngine::loadCountries(const json& data) {
    for(json c : data) {
        Country* country = new Country(c["name"]);

        for(int i = 0; i < c["units"].size(); ++i) {
            json::iterator it = c["units"][i].begin();
            countryUnitNames[country->getName()][it.key()] = it.value();
        }

        country->setBaseResourceCount(c["baseResourceCount"]);
        countries[c["name"]] = country;
    }
}

void WarEngine::loadAlliances(const json& data) {
    for(json a : data) {
        Alliance* alliance = new Alliance(a["name"]);

        for(int i = 0; i < a["countries"].size(); ++i) {
            alliance->addCountry(countries[a["countries"][i]]);
        }

        alliances[a["name"]] = alliance;
    }
}

// ============================================================================
// SIMULATION HELPER FUNCTIONS
// ============================================================================

void WarEngine::purchaseUnits(const json& data) {
    if(!data.is_array()) {
        throw WarException("Expected a JSON array.", "malformed_object");
    }

    for(json country : data) {
        for(json unit : country["units"]) {
            countries[country["name"]]->generateResources();
            for(int i = 0; i < unit["quantity"]; i++) {
                countries[country["name"]]->addEntity(
                    generateUnit(country["name"], unit["type"]));
            }
        }
    }
}

Unit* WarEngine::generateUnit(const std::string& country,
                              const std::string& type) {
    // TODO: Add check to make sure country and unit type exists
    std::string unitName = countryUnitNames[country][type];
    Unit* unit = NULL;

    if(type == "HeavyLandUnit") {
        unit = unitFactories["land"]->createHeavyUnit(unitName);
    } else if(type == "MediumLandUnit") {
        unit = unitFactories["land"]->createMediumUnit(unitName);
    } else if(type == "LightLandUnit") {
        unit = unitFactories["land"]->createLightUnit(unitName);
    } else if(type == "HeavySeaUnit") {
        unit = unitFactories["sea"]->createHeavyUnit(unitName);
    } else if(type == "MediumSeaUnit") {
        unit = unitFactories["sea"]->createMediumUnit(unitName);
    } else if(type == "LightSeaUnit") {
        unit = unitFactories["sea"]->createLightUnit(unitName);
    } else if(type == "HeavyAirUnit") {
        unit = unitFactories["air"]->createHeavyUnit(unitName);
    } else if(type == "MediumAirUnit") {
        unit = unitFactories["air"]->createMediumUnit(unitName);
    } else if(type == "LightAirUnit") {
        unit = unitFactories["air"]->createLightUnit(unitName);
    }

    if(!unit) {
        throw WarException("Could not generate Unit.", "malformed_request");
    }

    return unit;
}

// Think about output
void WarEngine::startSimulation(json war) {
    turnCounter = 1;
    player1Turn = true;
    bool warInProgress = true;

    // Round
    while(warInProgress) {
        // Phase 1
        for(int i = 0; i < 2; i++) {
            int player = player1Turn ? 1 : 2;
            std::cout << "\033[1;" << 32 + player << "mFaction: " << player
                      << std::endl
                      << "Turn: " << turnCounter << std::endl;
            displayResources();
            buyUnits();
            displayUnits();
            placeTroops();
            printMap();
            // std::cout<<"\033[1;32"<< 32 +
            // player<<"m======================================"<<std::endl;
            // std::cout<<std::endl;
            player1Turn = player1Turn ? false : true;
            std::cout << std::endl;
        }

        // Phase 2
        chooseStrategies();
        // viewStrategies();

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
    int resources = player1Turn ? factions[0]->getResourceCount()
                                : factions[1]->getResourceCount();
    std::string factionName =
        player1Turn ? factions[0]->getName() : factions[1]->getName();
    std::cout << factionName << " Resources: " << resources << std::endl;
    // std::cout<<std::endl;
}

void WarEngine::buyUnits() {
    // //displayUnitMenu();
    // if(player1Turn){
    //     std::cout<<factions[0]->getName()<<" buying troops"<<std::endl;
    //     std::cout<<"Name: "<<faction1UnitNames["MediumAirUnit"]<<std::endl;

    //     ((Country
    //     *)factions[0])->addUnit(unitFactories["land"]->createHeavyUnit(faction1UnitNames["HeavyLandUnit"]));
    //     //((Country
    //     *)factions[0])->addUnit(unitFactories["land"]->createLightUnit(faction1UnitNames["LightLandUnit"]));
    //     //((Country
    //     *)factions[0])->addUnit(unitFactories["land"]->createLightUnit(faction1UnitNames["LightLandUnit"]));
    //     ((Country
    //     *)factions[0])->addUnit(unitFactories["air"]->createHeavyUnit(faction1UnitNames["HeavyAirUnit"]));
    //     //((Country
    //     *)factions[0])->addUnit(unitFactories["sea"]->createHeavyUnit(faction1UnitNames["HeavySeaUnit"]));
    //     //((Country
    //     *)factions[0])->addUnit(unitFactories["sea"]->createHeavyUnit(faction1UnitNames["HeavySeaUnit"]));
    //     ((Country
    //     *)factions[0])->addUnit(unitFactories["sea"]->createHeavyUnit(faction1UnitNames["HeavySeaUnit"]));
    //     std::cout<<std::endl;
    // }
    // else{
    //     std::cout<<factions[1]->getName()<<" buying troops"<<std::endl;
    //     // ((Country
    //     *)factions[1])->addUnit(unitFactories["land"]->createHeavyUnit(faction2UnitNames["HeavyLandUnit"]));
    //     // ((Country
    //     *)factions[1])->addUnit(unitFactories["land"]->createHeavyUnit(faction2UnitNames["HeavyLandUnit"]));
    //     // ((Country
    //     *)factions[1])->addUnit(unitFactories["land"]->createHeavyUnit(faction2UnitNames["HeavyLandUnit"]));
    //     // ((Country
    //     *)factions[1])->addUnit(unitFactories["land"]->createHeavyUnit(faction2UnitNames["HeavyLandUnit"]));
    //     // ((Country
    //     *)factions[1])->addUnit(unitFactories["air"]->createHeavyUnit(faction2UnitNames["HeavyAirUnit"]));
    //     // ((Country
    //     *)factions[1])->addUnit(unitFactories["air"]->createMediumUnit(faction2UnitNames["MediumAirUnit"]));
    //     // ((Country
    //     *)factions[1])->addUnit(unitFactories["sea"]->createHeavyUnit(faction2UnitNames["HeavySeaUnit"]));
    //     ((Country
    //     *)factions[1])->addUnit(unitFactories["land"]->createLightUnit(faction1UnitNames["LightLandUnit"]));

    //     ((Country
    //     *)factions[1])->addUnit(unitFactories["air"]->createLightUnit(faction1UnitNames["LightAirUnit"]));

    //     ((Country
    //     *)factions[1])->addUnit(unitFactories["sea"]->createLightUnit(faction1UnitNames["LightSeaUnit"]));
    //     std::cout<<std::endl;
    // }
    // //std::cout << "Enter Unit Type (Land, Sea, Air): ";
    // //std::cout<<std::endl;
}

void WarEngine::displayUnits() {
    if(player1Turn) {
        std::cout << factions[0]->getName() << " Troops:" << std::endl;
        ((Country*)factions[0])->printUnits();
    } else {
        std::cout << factions[1]->getName() << " Troops:" << std::endl;
        ((Country*)factions[1])->printUnits();
    }
}
/**
 * @brief Add 'parent' to unit to know which theatre its in
 *  Need to make function to remove unit from a theatre when its moved parent
 * theatre pointer
 */

void WarEngine::placeTroops() {
    // if(player1Turn){
    //     std::cout<<factions[0]->getName()<<" troop
    //     movements:"<<std::endl<<std::endl; std::vector<std::pair<int,int>>
    //     movements = {std::pair<int,int>(0,0),
    //                                                  std::pair<int,int>(1,1),
    //                                                  std::pair<int,int>(2,2)};
    //     int moveCount = 3; //I want to move 3 troops - random

    //     for(int k =0; k < moveCount;k++){
    //         std::cout<<((Country*) factions[0])->getEntity(k)->getName()<<"
    //         moving to
    //         "<<theatres[movements[k].first][movements[k].second]->getName()<<std::endl;
    //         theatres[movements[k].first][movements[k].second]->addEntity(factions[0]->getName(),((Country*)
    //         factions[0])->getEntity(k));
    //     }
    // }
    // else{
    //     std::cout<<factions[1]->getName()<<" troop
    //     movements:"<<std::endl<<std::endl; std::vector<std::pair<int,int>>
    //     movements = {std::pair<int,int>(0,0),
    //                                                  std::pair<int,int>(1,1),
    //                                                  std::pair<int,int>(2,2)};
    //     int moveCount = 3; //I want to move 3 troops - random

    //     for(int k =0; k < moveCount;k++){
    //         std::cout<<((Country*) factions[1])->getEntity(k)->getName()<<"
    //         moving to
    //         "<<theatres[movements[k].first][movements[k].second]->getName()<<std::endl;
    //         theatres[movements[k].first][movements[k].second]->addEntity(factions[1]->getName(),((Country*)
    //         factions[1])->getEntity(k));
    //     }
    // }
}

void WarEngine::displayUnitMenu() {
    // std::cout<<"List of Available Units"<<std::endl;
    // if(player1Turn)
    // {
    //       int counter = 1;
    //       for (it = faction1UnitNames.begin(); it != faction1UnitNames.end();
    //       ++it) {
    //             if(counter == 1){
    //                 std::cout<<"Land:"<<std::endl;
    //             }
    //             else if(counter == 4){
    //                 std::cout<<"Sea:"<<std::endl;
    //             }
    //             else if(counter == 7){
    //                 std::cout<<"Air:"<<std::endl;
    //             }
    //             std::cout <<"\t"<<counter<<". "<< it->second<<std::endl;
    //             counter++;
    //        }
    // }
    // else{
    //     int counter = 1;
    //       for (it = faction2UnitNames.begin(); it != faction2UnitNames.end();
    //       ++it) {
    //             if(counter == 1){
    //                 std::cout<<"Land:"<<std::endl;
    //             }
    //             else if(counter == 4){
    //                 std::cout<<"Sea:"<<std::endl;
    //             }
    //             else if(counter == 7){
    //                 std::cout<<"Air:"<<std::endl;
    //             }
    //             std::cout <<"\t"<< counter<<". "<< it->second<<std::endl;
    //             counter++;
    //        }
    // }
    // std::cout<<std::endl;
}

void WarEngine::chooseStrategies() {
    // set of strategies for each faction - vector for scalability
    std::vector<std::vector<WarStrategy*>> strategies = {
        {new AttackStrategy("America"), new CounterStrategy("America"),
         new PlanStrategy("America")},
        {new PlanStrategy("Germany"), new AttackStrategy("Germany"),
         new CounterStrategy("Germany")}};

    std::vector<std::vector<std::pair<int, int>>> targets = {
        {std::pair<int, int>(0, 0), std::pair<int, int>(1, 1),
         std::pair<int, int>(2, 2)},
        {std::pair<int, int>(0, 0), std::pair<int, int>(1, 1),
         std::pair<int, int>(2, 2)}};

    int factionCounter = 0;
    for(std::vector<std::pair<int, int>> list : targets) {
        int strategyCounter = 0;
        for(std::pair<int, int> pair : list) {
            if(theatres[pair.first][pair.second]->checkForFaction(
                   factions[factionCounter]->getName())) {
                theatres[pair.first][pair.second]->changeStrategy(
                    factions[factionCounter]->getName(),
                    strategies[factionCounter][strategyCounter]);
            }
            strategyCounter++;
        }
        factionCounter++;
    }
}

void WarEngine::CommenceBattle() {
    std::cout << "Battle " << turnCounter << " commencing... " << std::endl;

    for(int i = 0; i < theatreSize; i++) {
        for(int j = 0; j < theatreSize; j++) {
            theatres[i][j]->battle();
        }
    }
    std::cout << std::endl;
}

WarEngine::~WarEngine() {
    for(int i = 0; i < theatreSize; i++) {
        for(int j = 0; j < theatreSize; j++) {
            delete theatres[i][j];
        }
        delete[] theatres[i];
    }
    delete theatres;

    std::unordered_map<std::string, UnitFactory*>::iterator it;
    for(it = unitFactories.begin(); it != unitFactories.end(); it++) {
        delete it->second;
    }
}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

void WarEngine::debug() {}

void WarEngine::printMap() {
    std::cout << "\033[0m=================MAP BEGIN================"
              << std::endl;
    for(int i = 0; i < theatreSize; i++) {
        for(int j = 0; j < theatreSize; j++) {
            theatres[i][j]->printTheatre();
        }
    }
    std::cout << "=================MAP END================" << std::endl;
    std::cout << std::endl;
}

std::string WarEngine::toLower(std::string& str) const {
    std::string lower = "";

    for(int i = 0; i < str.length(); i++) {
        lower += tolower(str[i]);
    }

    return lower;
}

void WarEngine::viewStrategies() {
    std::cout << "\033[1;32m=================TEST STRATS================="
              << std::endl;
    for(int i = 0; i < theatreSize; i++) {
        for(int j = 0; j < theatreSize; j++) {
            theatres[i][j]->printStrategies();
        }
    }
    std::cout << "\033[1;32m============================================="
              << std::endl;
}

std::vector<std::string> WarEngine::setToString(json array) {
    std::vector<std::string> str;
    for(std::string name : array) {
        str.push_back(name);
    }
    return str;
}
