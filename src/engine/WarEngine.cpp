#include "WarEngine.h"

#include <fstream>

#include "../entity/product/Engineers.h"
#include "../entity/product/FieldHospital.h"
#include "../faction/Country.h"

WarEngine* WarEngine::instance() {
    static WarEngine warEngine;
    return &warEngine;
}

WarEngine::WarEngine() {
    std::mt19937 engine;
    engine.seed(1);

    currentDay = 0;
    currentSimulation = -1;
    warStage = NULL;
    theatres = NULL;
    theatreSize = 0;

    loadSimulations();
}

WarEngine::~WarEngine() {
    reset();
}

void WarEngine::reset() {
    std::unordered_map<std::string, Alliance*>::iterator allianceIt;
    for(allianceIt = alliances.begin(); allianceIt != alliances.end();
        ++allianceIt) {
        // Leave uncommented for now, otherwise whole engine will die
        // delete allianceIt->second;
    }
    alliances.clear();

    std::unordered_map<std::string, Country*>::iterator countryIt;
    for(countryIt = countries.begin(); countryIt != countries.end();
        ++countryIt) {
        // Leave uncommented for now, otherwise whole engine will die
        // delete countryIt->second;
    }
    countries.clear();

    std::unordered_map<std::string, UnitFactory*>::iterator unitFactoryIt;
    for(unitFactoryIt = unitFactories.begin();
        unitFactoryIt != unitFactories.end(); ++unitFactoryIt) {
        delete unitFactoryIt->second;
    }
    unitFactories.clear();

    if(theatres) {
        for(int i = 0; i < theatreSize; i++) {
            for(int j = 0; j < theatreSize; j++) {
                delete theatres[i][j];
            }
            delete[] theatres[i];
        }
        delete[] theatres;
        theatres = NULL;
        theatreSize = 0;
    }

    if(warStage) {
        delete warStage;
        warStage = NULL;
    }

    countryUnitNames.clear();
    currentSimulation = -1;
    beforeBattle = true;
    currentDay = 0;
}

// ======================================================================================
// STARTUP FUNCTIONS
// ======================================================================================

void WarEngine::loadSimulations() {
    std::ifstream file("utilities/simulations.json");

    if(!file) {
        throw WarException("File containing simulations not found",
                           "file-not-found");
    }

    try {
        json data = json::parse(file);

        for(json simulation : data["Wars"]) {
            simulations.push_back(simulation);
        }
    } catch(json::exception& e) {
        throw WarException("Could not parse simulations file", "parse_error");
    }
}

json WarEngine::getAvailableSimulations() {
    json data;

    for(json s : simulations) {
        json j = json{{"name", s["WarTitle"]},
                      {"countries", json::array()},
                      {"alliances", json::array()}};

        for(json c : s["countries"]) {
            j["countries"].push_back({
                {"name", c["name"]},
                {"countryCode", c["countryCode"]},
            });
        }

        for(json a : s["alliances"]) {
            j["alliances"].push_back(a);
        }

        data.push_back(j);
    }

    return data;
}

void WarEngine::selectSimulation(int index) {
    if(index < 0 || index >= simulations.size()) {
        throw WarException("Not a valid simulation index", "out-of-bounds");
    }

    reset();
    loadSimulation(simulations[index]);

    currentDay = 0;
    beforeBattle = true;
    currentSimulation = index;
}

// ======================================================================================
// MAIN CONTROL FUNCTIONS
// ======================================================================================

void WarEngine::loadNextBattleDay() {
    if(currentSimulation == -1) {
        throw WarException("Load a simulation before loading next battle day",
                           "load_simulation");
    }
    if(simulations[currentSimulation].contains("duration") &&
       currentDay == simulations[currentSimulation]["duration"]) {
        throw WarException("End of simulation reached", "no_next_day");
    }
    if(!beforeBattle) {
        throw WarException(
            "Load battle day results before loading next battle day",
            "load_day_results");
    }

    json& data = simulations[currentSimulation]["days"][currentDay++];

    beforeBattle = false;
    currentDay = data["turnNumber"];
    loadWarFactors(data);
    generateCountryResources();
    loadResearch(data["research"]);
    purchaseUnits(data["unitsToPurchase"]);
    relocateUnits(data["unitsToRelocate"]);
    assignStrategies(data["strategies"]);
}

void WarEngine::loadBattleDayResults() {
    if(currentSimulation == -1) {
        throw WarException("Load a simulation before loading next battle day",
                           "load_simulation");
    }
    if(beforeBattle) {
        throw WarException("Load next battle day before loading day results",
                           "load_next_day");
    }

    for(int i = 0; i < theatreSize; i++) {
        for(int j = 0; j < theatreSize; j++) {
            theatres[i][j]->battle();
        }
    }

    beforeBattle = true;
}

void WarEngine::loadPreviousBattleDay() {
    if (currentSimulation == -1) {
        throw WarException("Load a simulation before loading previous battle day",
                           "load_simulation");
    }
    if(simulations[currentSimulation].contains("duration") && currentDay == 0) {
        throw WarException("At the beginning of simulation", "no_previous_day");
    }

    int day = --currentDay;
    selectSimulation(currentSimulation);

    for (int i = 0; i < day; i++) {
        loadNextBattleDay();
        if (i != day - 1) {
            loadBattleDayResults();
        }
    }
}

void WarEngine::loadSpecificBattleDay(int index) {
    if (currentSimulation == -1) {
        throw WarException("Load a simulation before loading a specific battle day",
                           "load_simulation");
    }
    if(index < 0 || index > simulations[currentSimulation]["duration"]) {
        throw WarException("Not a valid battle day index", "out-of-bounds");
    }

    selectSimulation(currentSimulation);

    for (int i = 0; i < index; i++) {
        loadNextBattleDay();
        if (i != index - 1) {
            loadBattleDayResults();
        }
    }
}

// ======================================================================================
// HELPER CONTROL FUNCTIONS
// ======================================================================================

void WarEngine::loadSimulation(const json& data) {
    if(!data.contains("countries")) {
        throw WarException("Malformed JSON object, countries not found.",
                           "malformed_countries");
    }

    if(!data.contains("alliances")) {
        throw WarException("Malformed JSON object, alliances not found.",
                           "malformed_alliances");
    }

    if(!data.contains("theatres")) {
        throw WarException("Malformed JSON object, theatres not found.",
                           "malformed_theatres");
    }

    unitFactories["land"] = new LandUnitFactory();
    unitFactories["sea"] = new SeaUnitFactory();
    unitFactories["air"] = new AirUnitFactory();

    loadCountries(data["countries"]);
    loadAlliances(data["alliances"]);
    loadTheatres(data["theatres"]);
    warStage = new EarlyStage("Initial Stage");
}

void WarEngine::loadCountries(const json& data) {
    for(json c : data) {
        Country* country = new Country(c["name"]);

        for(int i = 0; i < c["units"].size(); ++i) {
            json::iterator it = c["units"][i].begin();
            countryUnitNames[country->getName()][it.key()] = it.value();
        }

        country->setBaseResourceCount(c["baseResourceCount"]);
        country->setMobilization("CivilianEconomy");
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

void WarEngine::loadTheatres(const json& data) {
    theatreSize = pow(data.size(), 0.5);

    theatres = new Theatre**[theatreSize];

    for(int i = 0; i < theatreSize; i++) {
        theatres[i] = new Theatre*[theatreSize];
        for(int j = 0; j < theatreSize; j++) {
            int counter = theatreSize * i + j;
            theatres[i][j] = new Theatre(data[counter]["name"], true,
                                         data[counter]["resourceCount"]);
        }
    }
}

void WarEngine::loadWarFactors(const json& data) {
    loadEscalation(data["WarState"]);
    loadMobilization(data["mobilization"]);
}

// TODO: If time, change to produce JSON
void WarEngine::loadEscalation(const json& data) {
    std::string oldStage = "";
    Escalation* newWarStage = NULL;
    if(warStage) {
        oldStage = warStage->getState();
        newWarStage = warStage->checkStageOfWar(data);
        delete warStage;
        warStage = newWarStage;
    }
    if(warStage && newWarStage && oldStage != newWarStage->getState()) {
        // std::cout << "=============== NEW WAR PHASE: " << warStage->getState()
        //           << " ===============" << std::endl;
    }
}

void WarEngine::loadMobilization(const json& data) {
    for(json country : data["countries"]) {
        countries[country["name"]]->checkMobilization(warStage->getState(),
                                                      country["mobilization"]);
    }
}

void WarEngine::loadResearch(const json& data) {
    for(json country : data["countries"]) {
        countries[country["name"]]->setResearch(country["points"],
                                                country["research"]);
    }
}

// ======================================================================================
// SIMULATION HELPER FUNCTIONS
// ======================================================================================

void WarEngine::generateCountryResources() {
    if(alliances.size() == 0) {
        std::unordered_map<std::string, Country*>::iterator it =
            countries.begin();
        while(it != countries.end()) {
            int sum = 0;

            for(int i = 0; i < theatreSize; i++) {
                for(int j = 0; j < theatreSize; j++) {
                    sum += theatres[i][j]->getResource(it->first);
                }
            }
            countries[it->first]->generateResources(sum);
            it++;
        }
    } else {
        std::unordered_map<std::string, Alliance*>::iterator allianceIt =
            alliances.begin();
        while(allianceIt != alliances.end()) {
            int sum = 0;

            for(int i = 0; i < theatreSize; i++) {
                for(int j = 0; j < theatreSize; j++) {
                    std::unordered_map<std::string, Country*>::iterator
                        countryIt = countries.begin();
                    while(countryIt != countries.end()) {
                        sum += theatres[i][j]->getResource(countryIt->first);
                        countryIt++;
                    }
                }
            }
            alliances[allianceIt->first]->generateResources(sum);
            allianceIt++;
        }
    }
}

void WarEngine::purchaseUnits(const json& data) {
    if(!data.is_array()) {
        throw WarException("Expected a JSON array.", "malformed_object");
    }

    for(json country : data) {
        for(json unit : country["units"]) {
            for(int i = 0; i < unit["quantity"]; i++) {
                std::string special = "";
                if(unit.contains("special")) {
                    special = unit["special"];
                }

                countries[country["name"]]->addEntity(
                    generateUnit(country["name"], unit["type"], special));
            }
        }
    }
}

Entity* WarEngine::generateUnit(const std::string& country, const std::string& type,
                                const std::string& special) {
    // TODO: Add check to make sure country and unit type exists
    std::string unitName = countryUnitNames[country][type];
    Entity* unit = NULL;

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

    if(special == "engineers") {
        return new Engineers(unit);
    } else if(special == "fieldHospital") {
        return new FieldHospital(unit);
    }

    return unit;
}

void WarEngine::relocateUnits(const json& data) {
    if(!data.is_array()) {
        throw WarException("Expected a JSON array.", "malformed_object");
    }
    int cnt = 0;
    for(json country : data) {
        for(json unit : country["movements"]) {
            if(unit["destination"].get<std::string>() != "Flee") {
                std::pair<int, int> destination =
                    getLocation(unit["destination"]);
                transportUnit(theatres[destination.first][destination.second],
                              country["name"], unit["type"], unit["index"]);
            } else {
                std::string name = country["name"];
                Theatre* oldHome = ((Unit*)countries[name]->getEntity(
                                        unit["type"], unit["index"]))
                                       ->getTheatre();
                oldHome->removeEntity(name, unit["type"],
                                      ((Unit*)countries[name]->getEntity(
                                           unit["type"], unit["index"]))
                                          ->getId());
            }
            cnt++;
        }
    }
}

void WarEngine::transportUnit(Theatre* destination, const std::string& country,
                              const std::string& type, const int& index) {

    if (countries[country]->getArmedForce(type)->getUnitCount() - 1 < index || index < 0) {
        throw WarException("Transportation Error","index-not-found");
    }
    Theatre* oldHome =
        ((Unit*)countries[country]->getEntity(type, index))->getTheatre();
    if(oldHome) {
        
        destination->addEntity(
            country, oldHome->removeEntity(
                         country, type,
                         countries[country]->getEntity(type, index)->getId()));
    } else {
        
        destination->addEntity(
            country, ((Unit*)countries[country]->getEntity(type, index)));
    }
}

void WarEngine::assignStrategies(const json& data) {
    for(json country : data) {
        for(json strategy : country["strategies"]) {
            // std::cout<<strategy["theatre"].get<std::string>();
            // std::cout<<"here";
            std::pair<int, int> theatre = getLocation(strategy["theatre"]);

            if(theatres[theatre.first][theatre.second]->checkForFaction(
                   country["name"].get<std::string>())) {
                WarStrategy* strt;
                std::string str = strategy["strategy"].get<std::string>();
                std::string target = strategy["target"].get<std::string>();
                if(str == "Attack") {
                    strt = new AttackStrategy(target);
                } else if(str == "Counter") {
                    strt = new CounterStrategy(target);
                } else if(str == "Plan") {
                    strt = new PlanStrategy(target);
                } else {
                    throw WarException("strategy-not-found");
                }
                theatres[theatre.first][theatre.second]->changeStrategy(
                    countries[country["name"]]->getName(), strt);
            }
        }
    }
    // viewStrategies();
}

json WarEngine::clearCasualties() {
    json data = getTheatreUnits();

    for(int i = 0; i < data.size(); i++) {
        json& country = data[i];

        for(int j = 0; j < country["theatres"].size(); j++) {
            json& theatre = country["theatres"][j];

            for(int k = 0; k < theatre["units"].size(); k++) {
                json& unit = theatre["units"][k];

                if(unit["currentHP"] != 0) {
                    theatre["units"].erase(theatre["units"].begin() + k--);
                }
            }

            if(theatre["units"].size() == 0) {
                country["theatres"].erase(country["theatres"].begin() + j--);
            }
        }

        if(country["theatres"].size() == 0) {
            data.erase(data.begin() + i--);
        }
    }

    std::unordered_map<std::string, Country*>::iterator it;
    for(it = countries.begin(); it != countries.end(); it++) {
        it->second->clearCasualties();
    }

    return json{{"data", data}};
}

// TODO: If time, change to produce JSON
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

std::pair<int, int> WarEngine::getLocation(const json& data) {
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

// ======================================================================================
// JSON UTILITY FUNCTIONS
// ======================================================================================

json WarEngine::getStats() {
    return json{{"engine", getEngineStats()},
                {"casualties", clearCasualties()},
                {"countries", getCountryStats()},
                {"alliances", getAllianceStats()},
                {"theatreUnits", getTheatreUnits()},
                {"overallUnits", getOverallUnits()},
                {"theatres", getTheatreStats()},
                {"strategies", getStrategies()},
                {"mobilization", getMobilization()},
                {"research", getResearch()}};
}

json WarEngine::getEngineStats() {
    std::string stage = "Initial Stage";

    if(warStage) {
        if(warStage->getState() == "EarlyStage") {
            stage = "Early Stage";
        } else if(warStage->getState() == "MiddleStage") {
            stage = "Middle Stage";
        } else if(warStage->getState() == "LateStage") {
            stage = "Late Stage";
        }
    }

    return json{{"stage", stage},
                {"duration", simulations[currentSimulation]["duration"]},
                {"day", currentDay},
                {"numberOfCountries", countries.size()},
                {"numberOfAlliances", alliances.size()}};
}

json WarEngine::getCountryStats() {
    json array = json::array();

    std::unordered_map<std::string, Country*>::iterator it = countries.begin();
    while(it != countries.end()) {
        array.push_back(json{{"name", it->first},
                             {"resources", it->second->getResourceCount()},
                             {"totalUnits", it->second->getEntityCount()}});
        it++;
    }

    return json{{"data", array}};
}

json WarEngine::getAllianceStats() {
    json array = json::array();

    std::unordered_map<std::string, Alliance*>::iterator it = alliances.begin();
    while(it != alliances.end()) {
        array.push_back(
            json{{"name", it->first}, {"countries", it->second->toJSON()}});
        it++;
    }

    return json{{"data", array}};
}

json WarEngine::getOverallUnits() {
    json array = json::array();
    std::unordered_map<std::string, Country*>::iterator it = countries.begin();

    while(it != countries.end()) {
        array.push_back(
            json{{"name", it->first}, {"units", it->second->allUnitsToJSON()}});
        it++;
    }

    return json{{"data", array}};
}

json WarEngine::getTheatreStats() {
    json data = json::array();

    for(int i = 0; i < theatreSize; i++) {
        for(int j = 0; j < theatreSize; j++) {
            data.push_back(theatres[i][j]->toJSON(i, j));
        }
    }

    return json{{"data", data}};
}

json WarEngine::getTheatreUnits() {
    json data = json::array();
    std::unordered_map<std::string, std::string> coordinates;

    // Derive coordinates for each Theatre
    for(int i = 0; i < theatreSize; i++) {
        for(int j = 0; j < theatreSize; j++) {
            std::string c = std::to_string(i) + "-" + std::to_string(j);
            coordinates[theatres[i][j]->getName()] = c;
        }
    }

    std::unordered_map<std::string, Country*>::iterator it;

    // Get list of units for each country
    for(it = countries.begin(); it != countries.end(); ++it) {
        json j = it->second->getListOfUnits();
        for(json& theatre : j["theatres"]) {
            theatre["coordinates"] = coordinates[theatre["name"]];
        }
        data.push_back(j);
    }

    return data;
}

json WarEngine::getStrategies() {
    json data = json::array();
    std::string countryName = "";
    std::unordered_map<std::string, Country*>::iterator it = countries.begin();
    while(it != countries.end()) {
        countryName = it->first;
        json theatre = json::array();
        for(int i = 0; i < theatreSize; i++) {
            for(int j = 0; j < theatreSize; j++) {
                if(theatres[i][j]->checkForFaction(countryName) &&
                   theatres[i][j]->checkForStrategy(countryName)) {
                    theatre.push_back(json{
                        {"name", theatres[i][j]->getName()},
                        {"coordinates",
                         std::to_string(i) + "-" + std::to_string(j)},
                        {"strategy", theatres[i][j]->getStrategy(countryName)},
                        {"target", theatres[i][j]->getTarget(countryName)}});
                }
            }
        }
        data.push_back(json{{"country", countryName}, {"theatres", theatre}});
        it++;
    }

    return json{{"data", data}};
}

json WarEngine::getMobilization() {
    json data = json::array();
    std::unordered_map<std::string, Country*>::iterator it = countries.begin();
    while(it != countries.end()) {
        std::string m = it->second->getMobilization();
        if(m == "PartialMobilization") {
            m = "Partial";
        } else if(m == "TotalMobilization") {
            m = "Total";
        } else if(m == "WarEconomy") {
            m = "War Economy";
        } else if(m == "CivilianEconomy") {
            m = "Civilian Economy";
        }
        data.push_back(json{{"name", it->first}, {"mobilization", m}});
        it++;
    }
    return json{{"data", data}};
}

json WarEngine::getResearch() {
    json data = json::array();
    std::unordered_map<std::string, Country*>::iterator it = countries.begin();
    while(it != countries.end()) {
        data.push_back(it->second->researchToJSON());
        it++;
    }

    return json{{"data", data}};
}

Theatre* WarEngine::TestTheatre() {
    return theatres[0][0];
}

Theatre * WarEngine::findTheatre(std::string theatreName) {
    for(int i = 0; i < theatreSize; i++) {
        for(int j = 0; j < theatreSize; j++) {
            if(theatres[i][j]->getName() == theatreName){
                return theatres[i][j];
            }
        }
    }
    return NULL;
}
