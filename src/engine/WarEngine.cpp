#include "WarEngine.h"

#include <fstream>

#include "../faction/Country.h"

WarEngine *WarEngine::instance() {
    static WarEngine warEngine;
    return &warEngine;
}

WarEngine::WarEngine() {
    dayCounter = 0;
    srand(1);
    warStage = new EarlyStage("pre-war");
    unitFactories["land"] = new LandUnitFactory();
    unitFactories["sea"] = new SeaUnitFactory();
    unitFactories["air"] = new AirUnitFactory();
}

void WarEngine::loadTheatres(const json& data){
    theatreSize = pow(data.size(), 0.5);
    theatres = new Theatre **[theatreSize];

    for (int i = 0; i < theatreSize; i++) {
        theatres[i] = new Theatre *[theatreSize];
        for (int j = 0; j < theatreSize; j++) {
            int counter = theatreSize * i + j;
            theatres[i][j] = new Theatre(data[counter]["name"], true, data[counter]["resourceCount"]);
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
void WarEngine::loadWarFactors(const json& data){
    loadEscalation(data["WarState"]);
    loadMobilization(data["mobilization"]);
}


void WarEngine::loadMobilization(const json& data) {
    for (json country: data["countries"]) {
            countries[country["name"].get<std::string>()]->checkMobilization(warStage->getState(), country["mobilization"].get<std::string>()); 
    }
}

void WarEngine::loadResearch(const json& data){
    for(json country : data["countries"]){
        countries[country["name"].get<std::string>()]->setResearch(country["points"].get<int>(),country["research"].get<std::string>());
    }
}

void WarEngine::loadEscalation(const json &data) {

    std::string oldStage = warStage->getState();
    warStage = warStage->checkStageOfWar(data.get<std::string>());
    if (oldStage != warStage->getState()) {
        std::cout << "=============== NEW WAR PHASE: " << warStage->getState() << " ===============" << std::endl;
    }
}

void WarEngine::loadBattleDay(const json& data){
    loadWarFactors(data["rounds"][dayCounter]);
    generateCountryResources(data["countries"],data["alliances"]);
    loadResearch(data["rounds"][dayCounter]["research"]);
    

    purchaseUnits(data["rounds"][dayCounter]["unitsToPurchase"]);
    relocateUnits(data["rounds"][dayCounter]["unitsToRelocate"]);
    assignStrategies(data["rounds"][dayCounter]["strategies"]);
}

void WarEngine::goBack(){
    if(dayCounter != 0){
        dayCounter--;
    }
}

void WarEngine::generateCountryResources(const json& counts,const json& alls){
    int sum = 0;
    if(alliances.size()==0)
    {
        std::cout<<"Country Resources: "<<std::endl;
        for (json c: counts) {
            sum = 0;

            for (int i = 0; i < theatreSize; i++) { 
              for (int j = 0; j < theatreSize; j++) { 
               sum += theatres[i][j]->getResource(c["name"].get<std::string>());
             }
            }
            countries[c["name"].get<std::string>()]->generateResources(sum);
            std::cout<<c["name"].get<std::string>()<<": "<<countries[c["name"]]->getResourceCount()<<std::endl;
         }
    }
    else
    {
          for (json a: alls) {
            //std::cout<<"Name: "<<a["name"]<<": "<<std::endl;
           sum = 0;

            for (int i = 0; i < theatreSize; i++) { 
              for (int j = 0; j < theatreSize; j++) { 
                for (json country: a["countries"]) {
                    sum += theatres[i][j]->getResource(country.get<std::string>());
                    //std::cout<<theatres[i][j]->getName()<<" "<<sum<<std::endl;
                }
             }
            }
            alliances[a["name"].get<std::string>()]->generateResources(sum);
            alliances[a["name"].get<std::string>()]->printResources();
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
    if (oldHome) {
         //std::cout<<"Old: "<<oldHome->getName()<<" "<<((Unit *) countries[country]->getEntity(type, index))->getName()<<std::endl;
        destination->addEntity(country,oldHome->removeEntity(country, type, ((Unit *) countries[country]->getEntity(type, index))->getId()));
    }
    else{
        destination->addEntity(country,((Unit *) countries[country]->getEntity(type, index)));
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



// ============================================================================
// MAIN WAR FUNCTIONS
// ============================================================================





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
    dayCounter++;
}

json WarEngine::getRoundResults() {
    // clearCasualties();
    return json{};
}

json WarEngine::clearCasualties() {
    json data = getTheatreUnits();

    for (int i = 0; i < data.size(); i++) {
        json& country = data[i];
        
        for (int j = 0; j < country["theatres"].size(); j++) {
            json& theatre = country["theatres"][j];

            for (int k = 0; k < theatre["units"].size(); k++) {
                json& unit = theatre["units"][k];

                if (unit["currentHP"] != 0) {
                    theatre["units"].erase(theatre["units"].begin() + k--);
                }
            }

            if (theatre["units"].size() == 0) {
                country["theatres"].erase(country["theatres"].begin() + j--);
            }
        }

        if (country["theatres"].size() == 0) {
            data.erase(data.begin() + i--);
        }
    }

    std::unordered_map<std::string, Country*>::iterator it;
    for (it = countries.begin(); it != countries.end(); it++) {
        std::cout << "Jake" << std::endl;
        it->second->clearCasualties();
    }

    return data;
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

json WarEngine::getStats(){
    return json{{"engine", getEngineStats()},
                {"countries", getCountryStats()},
                {"alliances", getAllianceStats()},
                {"theatreUnits", getTheatreUnits()},
                {"overallUnits", getOverallUnits()},
                {"theatres" , getTheatreStats()}};
}

json WarEngine::getEngineStats() {
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
                 {"day", dayCounter},
                 {"numberOfCountries", countries.size()},
                 {"numberOfAlliances", alliances.size()}};
}

json WarEngine::getCountryStats() {
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

json WarEngine::getAllianceStats() {

    json array;
    std::unordered_map<std::string, Alliance *>::iterator it = alliances.begin();
    while(it != alliances.end()){
        array.push_back(json{{"name", it->first},
                             {"countries", it->second->toJSON()}});
        it++;
    }
    
    return json{{"data" , array}};
}

json WarEngine::getOverallUnits() {
    json array;
    std::unordered_map<std::string, Country *>::iterator it = countries.begin();

    while(it != countries.end()){
        array.push_back(json{{"name", it->first},
                             {"units", it->second->allUnitsToJSON()}});
        it++;
    }

    return json{{"data" , array}};
}

json WarEngine::getTheatreStats() {
    json data = json::array();
    
    for (int i = 0; i < theatreSize; i++) {
        for (int j = 0; j < theatreSize; j++) {
            data.push_back(theatres[i][j]->toJSON(i,j));
        }
    }

    return json{{"data", data}};
}

json WarEngine::getTheatreUnits() {
    json data;
    std::unordered_map<std::string, std::string> coordinates;

    // Derive coordinates for each Theatre
    for (int i = 0; i < theatreSize; i++) {
        for (int j = 0; j < theatreSize; j++) {
            std::string c = std::to_string(i) + "-" + std::to_string(j); 
            coordinates[theatres[i][j]->getName()] = c;
        }
    }

    std::unordered_map<std::string, Country *>::iterator it;

    // Get list of units for each country
    for (it = countries.begin(); it != countries.end(); ++it) {
        json j = it->second->getListOfUnits();
        for (json& theatre : j["theatres"]) {
            theatre["coordinates"] = coordinates[theatre["name"]];
        }
        data.push_back(j);
    }

    return data;
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

Theatre* WarEngine::getTheatre(){
    std::cout << theatres[0][0]->getName();
    return theatres[0][0];
}
