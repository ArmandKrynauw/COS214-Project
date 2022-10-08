#include "WarEngine.h"

WarEngine::WarEngine(){
    player1UnitNames.insert(std::pair<std::string,std::string>("LightLandUnit",""));
    player1UnitNames.insert(std::pair<std::string,std::string>("MediumLandUnit",""));
    player1UnitNames.insert(std::pair<std::string,std::string>("HeavyLandUnit",""));

    player1UnitNames.insert(std::pair<std::string,std::string>("LightSeaUnit",""));
    player1UnitNames.insert(std::pair<std::string,std::string>("MediumSeaUnit",""));
    player1UnitNames.insert(std::pair<std::string,std::string>("HeavySeaUnit",""));

    player1UnitNames.insert(std::pair<std::string,std::string>("LightAirUnit",""));
    player1UnitNames.insert(std::pair<std::string,std::string>("MediumAirUnit",""));
    player1UnitNames.insert(std::pair<std::string,std::string>("HeavyAirUnit",""));

    player2UnitNames.insert(std::pair<std::string,std::string>("LightLandUnit",""));
    player2UnitNames.insert(std::pair<std::string,std::string>("MediumLandUnit",""));
    player2UnitNames.insert(std::pair<std::string,std::string>("HeavyLandUnit",""));

    player2UnitNames.insert(std::pair<std::string,std::string>("LightSeaUnit",""));
    player2UnitNames.insert(std::pair<std::string,std::string>("MediumSeaUnit",""));
    player2UnitNames.insert(std::pair<std::string,std::string>("HeavySeaUnit",""));

    player2UnitNames.insert(std::pair<std::string,std::string>("LightAirUnit",""));
    player2UnitNames.insert(std::pair<std::string,std::string>("MediumAirUnit",""));
    player2UnitNames.insert(std::pair<std::string,std::string>("HeavyAirUnit",""));
}

void WarEngine::setPlayer1UnitNames(std::string arr[]){
    int counter = 0;
    for(it = player1UnitNames.begin() ; it != player1UnitNames.end(); ++it){
        it->second = arr[0];
        counter++;
    }
}

void WarEngine::setPlayer2UnitNames(std::string arr[]){
    int counter = 0;
    for(it = player2UnitNames.begin() ; it != player2UnitNames.end(); ++it){
        it->second = arr[0];
        counter++;
    }
}

void WarEngine::startSimulatino(){
    
}
WarEngine::~WarEngine(){

}