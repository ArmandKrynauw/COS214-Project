#include "WarEngine.h"

#include <fstream>

#include "../faction/Country.h"

WarEngine *WarEngine::instance() {
    static WarEngine warEngine;
    return &warEngine;
}

WarEngine::WarEngine() {
    roundCounter = 0;
    srand(1);
    warStage = new EarlyStage("pre-war");
    unitFactories["land"] = new LandUnitFactory();
    unitFactories["sea"] = new SeaUnitFactory();
    unitFactories["air"] = new AirUnitFactory();
}

void WarEngine::loadTheatres(const json& data){
    theatreSize = 3;
    theatres = new Theatre **[theatreSize];
    int counter = 0;
    for (int i = 0; i < theatreSize; i++) {
        theatres[i] = new Theatre *[theatreSize];
        for (int j = 0; j < theatreSize; j++) {
            theatres[i][j] =
                    new Theatre(data[counter]["name"].get<std::string>(),
                                true, data[counter]["resourceCount"].get<int>());  // defaut all theatres sea for testing
            counter++;
        }
    }
}

void WarEngine::loadSimulation(const json &simulation) {
    if (!simulation.contains("countries")) {
        throw WarException("Malformed JSON object, countries not found.",
                           "malformed_countries");
    }
    
    loadCountries(simulation["countries"]);

    if (simulation.contains("alliances")) {
        loadAlliances(simulation["alliances"]);
    }

    warDuration = simulation["duration"];
}

void WarEngine::loadCountries(const json &data) {
    for (json c: data) {
        Country *country = new Country(c["name"]);

        for (int i = 0; i < c["units"].size(); ++i) {
            json::iterator it = c["units"][i].begin();
            countryUnitNames[country->getName()][it.key()] = it.value();
        }

        country->setBaseResourceCount(c["baseResourceCount"]);
        country->setMobilization("PartialMobilization");
        countries[c["name"]] = country;
    }
}

void WarEngine::loadAlliances(const json &data) {
    for (json a: data) {
        Alliance *alliance = new Alliance(a["name"]);

        for (int i = 0; i < a["countries"].size(); ++i) {
            alliance->addCountry(countries[a["countries"][i]]);
        }

        alliances[a["name"]] = alliance;
    }
}


// ============================================================================
// SIMULATION HELPER FUNCTIONS
// ============================================================================
void WarEngine::checkMobilization(const json& data) {
    roundCounter++;
    for (json country: data["countries"]) {
            countries[country["name"].get<std::string>()]->checkMobilization(warStage->getState(), country["mobilization"].get<std::string>()); 
    }
}


void WarEngine::generateCountryResources(const json& counts,const json& alls){
    int sum = 0;
    if(alliances.size()==0)
    {
        for (json c: counts) {
            sum = 0;

            for (int i = 0; i < theatreSize; i++) { 
              for (int j = 0; j < theatreSize; j++) { 
               sum += theatres[i][j]->getResource(c["name"].get<std::string>());
               //std::cout<<sum<<std::endl;
             }
            }
            countries[c["name"].get<std::string>()]->generateResources(sum);
         }
    }
    else
    {
       for (json a: alls) {

           sum = 0;

            for (int i = 0; i < theatreSize; i++) { 
              for (int j = 0; j < theatreSize; j++) { 
               sum += theatres[i][j]->getResource(a["name"].get<std::string>());
             }
            }
            alliances[a["name"].get<std::string>()]->generateResources(sum);
         }

    }
}

void WarEngine::purchaseUnits(const json &data) {
    // generateCountryResources();
    if (!data.is_array()) {
        throw WarException("Expected a JSON array.", "malformed_object");
    }

    for (json country: data) {
        for (json unit: country["units"]) {
            for (int i = 0; i < unit["quantity"]; i++) {
                countries[country["name"]]->addEntity(
                        generateUnit(country["name"], unit["type"]));
            }
        }
    }
}

Unit *WarEngine::generateUnit(const std::string &country,
                              const std::string &type) {
    // TODO: Add check to make sure country and unit type exists
    std::string unitName = countryUnitNames[country][type];
    Unit *unit = NULL;

    if (type == "HeavyLandUnit") {
        unit = unitFactories["land"]->createHeavyUnit(unitName);
    } else if (type == "MediumLandUnit") {
        unit = unitFactories["land"]->createMediumUnit(unitName);
    } else if (type == "LightLandUnit") {
        unit = unitFactories["land"]->createLightUnit(unitName);
    } else if (type == "HeavySeaUnit") {
        unit = unitFactories["sea"]->createHeavyUnit(unitName);
    } else if (type == "MediumSeaUnit") {
        unit = unitFactories["sea"]->createMediumUnit(unitName);
    } else if (type == "LightSeaUnit") {
        unit = unitFactories["sea"]->createLightUnit(unitName);
    } else if (type == "HeavyAirUnit") {
        unit = unitFactories["air"]->createHeavyUnit(unitName);
    } else if (type == "MediumAirUnit") {
        unit = unitFactories["air"]->createMediumUnit(unitName);
    } else if (type == "LightAirUnit") {
        unit = unitFactories["air"]->createLightUnit(unitName);
    }

    if (!unit) {
        throw WarException("Could not generate Unit.", "malformed_request");
    }

    return unit;
}


void WarEngine::relocateUnits(const json &data) {
    if (!data.is_array()) {
        throw WarException("Expected a JSON array.", "malformed_object");
    }
    int cnt = 0;
    for (json country: data) {
        for (json unit: country["movements"]) {
            std::pair<int, int> destination = getLocation(unit["destination"]);
            std::string name = (countries[country["name"]]->inAlliance()) ? 
                                countries[country["name"]]->getAlliance()->getName() : country["name"].get<std::string>();

            transportUnit(theatres[destination.first][destination.second], name,
                          unit["type"].get<std::string>(), unit["index"].get<int>());
            cnt++;
        }

    }
}

void WarEngine::transportUnit(Theatre *destination, const std::string &country, const std::string &type, const int &index) {
    Theatre *oldHome = ((Unit *) countries[country]->getEntity(type, index))->getTheatre();
    destination->addEntity(country, countries[country]->getEntity(type, index));
    if (oldHome) {
        oldHome->removeEntity(country, type, ((Unit *) countries[country]->getEntity(type, index))->getId());
    }
}

void WarEngine::assignStrategies(const json &data) {
    for (json country: data) {
        for (json strategy: country["strategies"]) {
            // std::cout<<strategy["theatre"].get<std::string>();
            // std::cout<<"here";
            std::pair<int, int> theatre = getLocation(strategy["theatre"]);

            if (theatres[theatre.first][theatre.second]->checkForFaction(country["name"].get<std::string>())) {
                WarStrategy *strt;
                std::string str = strategy["strategy"].get<std::string>();
                std::string target = strategy["target"].get<std::string>();
                if (str == "Attack") {
                    strt = new AttackStrategy(target);
                } else if (str == "Counter") {
                    strt = new CounterStrategy(target);
                } else if (str == "Plan") {
                    strt = new PlanStrategy(target);
                } else {
                    throw WarException("strategy-not-found");
                }
                theatres[theatre.first][theatre.second]->changeStrategy(countries[country["name"]]->getName(), strt);
            }
        }
    }
    //viewStrategies();
}

void WarEngine::checkEscalation(const json &data) {

    std::string oldStage = warStage->getState();
    warStage = warStage->checkStageOfWar(data.get<std::string>());
    if (oldStage != warStage->getState()) {
        std::cout << "=============== NEW WAR PHASE: " << warStage->getState() << " ===============" << std::endl;
    }
}

// ============================================================================
// MAIN WAR FUNCTIONS
// ============================================================================

void WarEngine::startSimulation(json war) {
    // turnCounter = 1;
    // player1Turn = true;
    // bool warInProgress = true;

    // // Round
    // while(warInProgress) {
    //     // Phase 1
    //     for(int i = 0; i < 2; i++) {
    //         int player = player1Turn ? 1 : 2;
    //         std::cout << "\033[1;" << 32 + player << "mFaction: " << player
    //                   << std::endl
    //                   << "Turn: " << turnCounter << std::endl;
    //         displayResources();
    //         buyUnits();
    //         displayUnits();
    //         placeTroops();
    //         printMap();
    //         // std::cout<<"\033[1;32"<< 32 +
    //         // player<<"m======================================"<<std::endl;
    //         // std::cout<<std::endl;
    //         player1Turn = player1Turn ? false : true;
    //         std::cout << std::endl;
    //     }

    //     // Phase 2
    //     chooseStrategies();
    //     // viewStrategies();

    //     // Phase 3
    //     CommenceBattle();
    //     CommenceBattle();
    //     CommenceBattle();
    //     printMap();

    //     // Switch Order of players taking turns for fairness
    //     player1Turn = player1Turn ? false : true;
    //     // To end while loop for testing
    //     warInProgress = false;
    //     // SAVE STATE HERE
    //     turnCounter++;
    // }
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

}

void WarEngine::displayUnits() {

    std::cout << "Germany" << " Troops:" << std::endl;
    std::cout << countries["Germany"]->getListOfUnits() << std::endl;

    std::cout << "America" << " Troops:" << std::endl;
    std::cout << countries["America"]->getListOfUnits() << std::endl;

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
    // std::vector<std::vector<WarStrategy*>> strategies = {
    //     {new AttackStrategy("America"), new CounterStrategy("America"),
    //      new PlanStrategy("America")},
    //     {new PlanStrategy("Germany"), new AttackStrategy("Germany"),
    //      new CounterStrategy("Germany")}};

    // std::vector<std::vector<std::pair<int, int>>> targets = {
    //     {std::pair<int, int>(0, 0), std::pair<int, int>(1, 1),
    //      std::pair<int, int>(2, 2)},
    //     {std::pair<int, int>(0, 0), std::pair<int, int>(1, 1),
    //      std::pair<int, int>(2, 2)}};

    // int factionCounter = 0;
    // for(std::vector<std::pair<int, int>> list : targets) {
    //     int strategyCounter = 0;
    //     for(std::pair<int, int> pair : list) {
    //         if(theatres[pair.first][pair.second]->checkForFaction(
    //                factions[factionCounter]->getName())) {
    //             theatres[pair.first][pair.second]->changeStrategy(
    //                 factions[factionCounter]->getName(),
    //                 strategies[factionCounter][strategyCounter]);
    //         }
    //         strategyCounter++;
    //     }
    //     factionCounter++;
    // }
}

void WarEngine::CommenceBattle() {
    for (int i = 0; i < theatreSize; i++) {
        for (int j = 0; j < theatreSize; j++) {
            theatres[i][j]->battle();
        }
    }
}

json WarEngine::getRoundResults() {
    // clearCasualties();
    return json{};
}

json WarEngine::clearCasualties() {
    std::unordered_map<std::string, Country *>::iterator it;
    for (it = countries.begin(); it != countries.end(); ++it) {
        it->second->removeCasualties();
    }
    return json{};
}


WarEngine::~WarEngine() {
    for (int i = 0; i < theatreSize; i++) {
        for (int j = 0; j < theatreSize; j++) {
            delete theatres[i][j];
        }
        delete[] theatres[i];
    }
    delete theatres;

    std::unordered_map<std::string, UnitFactory *>::iterator it;
    for (it = unitFactories.begin(); it != unitFactories.end(); it++) {
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
    for (int i = 0; i < theatreSize; i++) {
        for (int j = 0; j < theatreSize; j++) {
            theatres[i][j]->printTheatre();
        }
    }
    std::cout << "=================MAP END================" << std::endl;
    std::cout << std::endl;
}

std::string WarEngine::toLower(std::string &str) const {
    std::string lower = "";

    for (int i = 0; i < str.length(); i++) {
        lower += tolower(str[i]);
    }

    return lower;
}

void WarEngine::viewStrategies() {
    std::cout << "\033[1;32m=================TEST STRATS================="
              << std::endl;
    for (int i = 0; i < theatreSize; i++) {
        for (int j = 0; j < theatreSize; j++) {
            theatres[i][j]->printStrategies();
        }
    }
    std::cout << "\033[1;32m============================================="
              << std::endl;
}

// ============================================================================
// JSON UTILITY FUNCTIONS
// ============================================================================

json WarEngine::getCountryUnits() {
    json data;

    std::unordered_map<std::string, Country *>::iterator it;
    for (it = countries.begin(); it != countries.end(); ++it) {
        data.push_back(it->second->getListOfUnits());
    }

    return data;
}

json WarEngine::getStats(){
    return json{{"engine", getEngineStats()},
                {"countries", getCountryStats()},
                {"alliances", getAllianceStats()},
                {"overallUnits", getOverallUnits()},
                {"theatres" , getTheatreStats()}};
}

json WarEngine::getEngineStats(){
    std::string stage;
    if(warStage->getState() == "EarlyStage"){
        stage = "Early Stage";
    }
    else if(warStage->getState() == "MiddleStage"){
        stage = "Middle Stage";
    }else if(warStage->getState() == "LateStage"){
        stage = "Late Stage";
    }
    return json {{"stage" , stage},
                 {"duration", warDuration},
                 {"day", roundCounter},
                 {"numberOfCountries", countries.size()},
                 {"numberOfAlliances", alliances.size()}};
}

json WarEngine::getCountryStats(){
    json array;
    std::unordered_map<std::string, Country *>::iterator it = countries.begin();
    while(it != countries.end()){
        array.push_back(json{{"name", it->first},
                             {"resources", it->second->getResourceCount()},
                             {"totalUnits", it->second->getEntityCount()}});
        it++;
    }
    
    return json{{"data" , array}};
}

json WarEngine::getAllianceStats(){

    json array;
    std::unordered_map<std::string, Alliance *>::iterator it = alliances.begin();
    while(it != alliances.end()){
        array.push_back(json{{"name", it->first},
                             {"countries", it->second->toJSON()}});
        it++;
    }
    
    return json{{"data" , array}};
}

json WarEngine::getOverallUnits(){
    json array;
    std::unordered_map<std::string, Country *>::iterator it = countries.begin();

    while(it != countries.end()){
        array.push_back(json{{"name", it->first},
                             {"units", it->second->allUnitsToJSON()}});
        it++;
    }

    return json{{"data" , array}};
}

json WarEngine::getTheatreStats(){
    json data = json::array();
    
    for (int i = 0; i < theatreSize; i++) {
        for (int j = 0; j < theatreSize; j++) {
            data.push_back(theatres[i][j]->toJSON(i,j));
        }
    }

    return json{{"data", data}};
}

std::vector<std::string> WarEngine::setToString(json array) {
    std::vector<std::string> str;
    for (std::string name: array) {
        str.push_back(name);
    }
    return str;
}

std::pair<int, int> WarEngine::getLocation(const json &data) {
    std::stringstream ss(data.get<std::string>());
    std::pair<int, int> destination;
    std::string row, col;
    std::getline(ss, row, ',');
    std::getline(ss, col);
    std::stringstream ss2(row);
    std::stringstream ss3(col);
    ss2 >> destination.first;
    ss3 >> destination.second;
    return destination;
}
