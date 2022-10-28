#include "client.h"
#include <iostream>
#include "../engine/WarEngine.h"
//#include "../engine/WarEngine.cpp"

Client::Client(){

}



void Client::Run(){
    std::cout<<"\033[1;32m================== CLIENT BOOTUP =================="<<std::endl;
    std::cout<<std::endl;

    //Different Country Unit Names
    availableCountries.push_back("Germany");
    // std::vector<std::string> germany{"Foot Soldier","BMP-3","Leopard 2A7",
    //                                  "Baden-Württemberg class","Braunschweig class","Type 212 Submarine",
    //                                  "CH-53G","Eurofighter Typhoon","Luftwaffe A400M"};

    std::vector<std::string> germany{"Luftwaffe A400M","Leopard 2A7","Type 212 Submarine",
                                     "CH-53G","Foot Soldier","Baden-Württemberg class",
                                     "Eurofighter Typhoon","BMP-3","Braunschweig class"};

    countries.insert(std::pair<std::string,std::vector<std::string>>("Germany",germany));
    
    availableCountries.push_back("America");
    // std::vector<std::string> america{"Foot Soldier","HMMWV","M1 Abrams",
    //                                  "Cruiser","Destroyer","USS Nebraska (SSBN-739)",
    //                                  "F-22A Raptors","A-10","C-17"};

    std::vector<std::string> america{"C-17","M1 Abrams","USS Nebraska (SSBN-739)",
                                     "F-22A Raptors","Foot Soldier","Cruiser",
                                    "A-10","HMMWV","Destroyer"};

    countries.insert(std::pair<std::string,std::vector<std::string>>("America",america));


    
    
    /**Assign Country for each side of the simulation*/
    std::pair<std::string,std::string> choices = getPlayerCountries();
    //std::cout<<"here"<<std::endl;
    WarEngine::instance()->setFaction1UnitNames(countries[choices.first]);
    WarEngine::instance()->setFaction2UnitNames(countries[choices.second]);
    //std::cout<<"here"<<std::endl;
    
    WarEngine::instance()->setCountryNames(choices);
    //std::cout<<"here"<<std::endl;

    WarEngine::instance()->setsFactionBaseResoures(350,400);



    std::cout<<"War to take place: "<<choices.first<< " Vs " <<choices.second<<std::endl;
    std::cout<<std::endl;
    printHeader();
   WarEngine::instance()->startSimulation();

    printFooter();
}

std::pair<std::string,std::string> Client::getPlayerCountries(){
    std::cout<<"Available countries: "<<std::endl;
    std::string str = "";
    for(std::pair<std::string,std::vector<std::string>> pair : countries){
        str = str + pair.first + ", ";
    }
    str = str.substr(0,str.length()-2);
    std::cout<<str<<std::endl;
    std::cout<<std::endl;

    std::pair<std::string,std::string> inputs;
    // std::cout<<"\033[1;33mPlayer 1 -> Enter name of country you woud like to play: ";
    // std::cin >> inputs.first;
    // std::cout<<std::endl;
    // std::cout<<"\033[1;34mPlayer 2 -> Enter name of country you woud like to play: ";
    // std::cin >> inputs.second;
    // std::cout<<std::endl;

    inputs.first = "Germany";
    inputs.second = "America";
    return inputs;
}

void Client::printHeader(){
    std::cout<<"\033[1;32m=============== START OF SIMULATION ===============\033[0m"<<std::endl;
    std::cout<<std::endl;
}

void Client::printFooter(){
    std::cout<<std::endl;
    std::cout<<"\033[1;32m================= END OF SIMULATION =================\033[0m"<<std::endl;
    
}