#include "WarEngine.h"
#include "../faction/Country.h"

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

void WarEngine::setPlayer1UnitNames(std::vector<std::string> names){
    int counter = 0;
    for(it = player1UnitNames.begin() ; it != player1UnitNames.end(); ++it){
        it->second = names[0];
        counter++;
    }
}

void WarEngine::setPlayer2UnitNames(std::vector<std::string> names){
    int counter = 0;
    for(it = player2UnitNames.begin() ; it != player2UnitNames.end(); ++it){
        it->second = names[0];
        counter++;
    }
}

void WarEngine::setCountryNames(std::pair<std::string,std::string> names){
    player1 = new Country(names.first);
    player2 = new Country(names.second);
}

//Think about output
void WarEngine::startSimulation(){
    turnCounter = 1;
    player1Turn = true;
    bool warInProgress = true;

    while(warInProgress){

        for(int i = 0;i < 2; i++){
            int player = player1Turn ? 1 : 2;
            std::cout<<"\033[1;" << 32 + player<<"mPlayer: "<< player <<" Turn: "<<turnCounter<<" ===================="<<std::endl;
            displayResources();
            //buyTroops();
            //PlaceTroops();
        std::cout<<"\033[1;32"<< 32 + player<<"m======================================"<<std::endl;
        std::cout<<std::endl;
        player1Turn = player1Turn ? false : true;
        }



        for(int i = 0;i < 2; i++){
            chooseStrategies();
            player1Turn = player1Turn ? false : true;
        }

        CommenceBattle();

        //Switch Order of players taking turns for fairness
        player1Turn = player1Turn ? false : true;
        //To end while loop for testing
        warInProgress = false;
    }

}

void WarEngine::displayResources(){
    int resources = player1Turn ? player1->getResourceCount() : player2->getResourceCount();
    std::cout << "Your Resources: " << resources << std::endl;
    
}

void WarEngine::chooseStrategies(){
    if(player1Turn){
        player1->chooseStrategy();
    }
    else{
        player2->chooseStrategy();
    }
}

void WarEngine::CommenceBattle(){

}

WarEngine::~WarEngine(){

}