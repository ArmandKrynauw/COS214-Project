#include "client.h"
#include <iostream>
#include "../engine/WarEngine.h"
#include "../engine/WarEngine.cpp"

int main(){

    WarEngine *  engine = new WarEngine();
    
    std::string germany[] = {"Foot Soldier","BMP-3","Leopard 2A7",
                             "Baden-Württemberg class","Braunschweig class","Type 212 Submarine",
                             "CH-53G","Eurofighter Typhoon","Luftwaffe A400M"};
    std::string america[] = {"Foot Soldier","HMMWV","M1 Abrams",
                             "Cruiser","Destroyer","USS Nebraska (SSBN-739)",
                             "F-22A Raptors","A-10","C-17"};


    engine->setPlayer1UnitNames(germany);
    engine->setPlayer2UnitNames(america);

    engine->startSimulatino();
    

    delete engine;
    return 0;
}