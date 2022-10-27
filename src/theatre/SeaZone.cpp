#include "SeaZone.h"SeaZone

SeaZone::SeaZone(std::string name) : Zone(name) {
    this->name+="_SeaZone";
}

std::string SeaZone::getType(){
    return "sea";
}

void SeaZone::takeDamage(int damage)
{
    // Ships tend to have very low engagement rates, while having much higher decisive battles

    int divisor = units.size()/2; 

    int hit = damage/divisor;
    int random;


    for (int i = 0; i < divisor; i++)
    {
        srand(time(NULL)+rand());
        random = (rand()%units.size()) +0;
        if(units.at(random)->takeDamage(hit))   // Unit died
        {
            units.at(random)->~Unit();
            units.erase(units.begin()+random-1);
        }
    }
    
    
}

SeaZone::~SeaZone() {}