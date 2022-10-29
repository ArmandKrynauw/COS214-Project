#include "LandZone.h"

LandZone::LandZone(std::string name) : Zone(name) {
    this->name+="_LandZone";
}

std::string LandZone::getType(){
    return "land";
}

void LandZone::takeDamage(int damage){
    // Ground forces tend to have unpredictable engagements just as often as expected engagements.
    
    int divisor = units.size(); 
    //std::cout<<divisor<<std::endl;
    int hit = damage/divisor;
    int random = 0;

    //std::cout<<"D:"<<damage<<std::endl;
    for (int i = 0; i < divisor; i++){
        srand(time(NULL)+rand());
        random = (rand()%units.size()) + 0;
        if(units.at(random)->takeDamage(hit)){
            delete units[random];
            units.erase(units.begin()+random);
        }
    }
    
    //std::cout<<"here"<<std::endl;
}

LandZone::~LandZone() {}