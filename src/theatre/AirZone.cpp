#include "AirZone.h"

AirZone::AirZone(std::string name) : Zone(name) {
    this->name+="_AirZone";
}

std::string AirZone::getType(){
    return "air";
}

void AirZone::takeDamage(int damage)
{
    // Planes have much higher contact rates with the enemy, however lower losses per engagement generally.

    int divisor = units.size()*2; 

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

AirZone::~AirZone() {}