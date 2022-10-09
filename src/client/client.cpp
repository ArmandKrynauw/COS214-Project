#include "client.h"
#include <iostream>
#include "../engine/WarEngine.h"
//#include "../engine/WarEngine.cpp"

Client::Client(){

}



void Client::Run(){

    
    //Singular Engine to run Simulations
    WarEngine * engine = new WarEngine();

    //Different Country Unit Names
    availableCountries.push_back("Germany");
    std::vector<std::string> germany{"Foot Soldier","BMP-3","Leopard 2A7",
                                     "Baden-Württemberg class","Braunschweig class","Type 212 Submarine",
                                     "CH-53G","Eurofighter Typhoon","Luftwaffe A400M"};

    countries.insert(std::pair<std::string,std::vector<std::string>>("Germany",germany));
    
    availableCountries.push_back("America");
    std::vector<std::string> america{"Foot Soldier","HMMWV","M1 Abrams",
                                     "Cruiser","Destroyer","USS Nebraska (SSBN-739)",
                                     "F-22A Raptors","A-10","C-17"};

    countries.insert(std::pair<std::string,std::vector<std::string>>("America",america));


    printHeader();

    //Players Decide Countries
    std::pair<std::string,std::string> choices = getPlayerCountries();
    engine->setPlayer1UnitNames(countries[choices.first]);
    engine->setPlayer2UnitNames(countries[choices.second]);
    
    engine->setCountryNames(choices);

    engine->startSimulation();

    printFooter();
    delete engine;
}

std::pair<std::string,std::string> Client::getPlayerCountries(){
    std::pair<std::string,std::string> inputs;
    std::cout<<"\033[1;33mPlayer 1 -> Enter name of country you woud like to play: ";
    std::cin >> inputs.first;
    std::cout<<std::endl;
    std::cout<<"\033[1;34mPlayer 2 -> Enter name of country you woud like to play: ";
    std::cin >> inputs.second;
    std::cout<<std::endl;
    return inputs;
}

void Client::printHeader(){
    std::cout<<"\033[1;32m====================================================="<<std::endl;
    std::cout<<"================ START OF SIMULATION ================"<<std::endl;
    std::cout<<"====================================================="<<std::endl;
    std::cout<<std::endl;
}

void Client::printFooter(){
    std::cout<<std::endl;
    std::cout<<"\033[1;32m====================================================="<<std::endl;
    std::cout<<"================= END OF SIMULATION ================="<<std::endl;
    std::cout<<"====================================================="<<std::endl;
}