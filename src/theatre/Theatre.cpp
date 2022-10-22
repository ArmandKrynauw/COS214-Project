#include "Theatre.h"

Theatre::Theatre(std::string name, bool seaZone)
{
    this->name = name;
    this->id = uuid::generate();
    if(seaZone) this->limit = 3;
    else
    this->limit = 2;
}

Theatre::~Theatre()
{
    
}

void Theatre::addFaction(std::string name)
{
    int num = factions.size();
    factions.insert({name,num});

    std::vector<Zone*> army;

    army.push_back(landFactory->createZone(name));
    army.push_back(airFactory->createZone(name));
    if(limit==3) army.push_back(seaFactory->createZone(name));

    armies.push_back(army);
}

void Theatre::removeFaction(std::string name)
{
    auto it = factions.find(name);
    int index = it->second;

    armies.at(index).at(0)->~Zone();
    armies.at(index).at(1)->~Zone();
    if(limit==3) armies.at(index).at(2)->~Zone();

    armies.erase(armies.begin()+index-1);
}

std::string Theatre::getName() const {
    return name;
}

void Theatre::addUnit(std::string faction,Unit* unit)
{
    auto it = factions.find(name);
    int index = it->second;

    if(unit->getType()=="air")
    armies.at(index).at(1)->addUnit(unit);
}

Unit* Theatre::removeUnit(std::string faction,int type,int index)
{
    auto it = factions.find(name);
    int index = it->second;


    Unit* unit =  armies.at(index).at(type)->removeUnit(index);

    return unit;
}

void Theatre::Battle(std::string attacker,std::string defender)
{
    auto it = factions.find(attacker);
    int indexAttacker = it->second;

    it = factions.find(defender);
    int indexDefender = it->second;

    int attackModifier = strategies.at(indexAttacker)->executeStrategy(strategies.at(indexDefender));
    int defendModifier = strategies.at(indexDefender)->executeStrategy(strategies.at(indexAttacker));

    int attackFinal;
    int defendFinal;

    for(int i = 0 ; i < limit; i++)
    {
        attackFinal = armies.at(indexAttacker).at(i)->sum()*attackModifier;
        defendFinal = armies.at(indexDefender).at(i)->sum()*defendModifier;

        armies.at(indexAttacker).at(i)->takeDamage(defendFinal);  // defender deals damage
        armies.at(indexDefender).at(i)->takeDamage(attackFinal);  // attacker deals damage
    }

    //would probably want to display results here
    return;

}

void Theatre::changeStrategy(std::string faction,std::string strat)
{
    auto it = factions.find(faction);
    int index = it->second;

    WarStrategy* strategy;

  if(strat=="plan")
  {
    strategy = new PlanStrategy();
    strategies.at(index)->~WarStrategy();

  }
  else
  if(strat=="attack")
  {
    strategy = new AttackStrategy();
    if(strategies.at(index)->getPlanned()) strategy->setPlanned(true);
    strategies.at(index)->~WarStrategy();
  }
  else
  if(strat=="counter")
  {
    strategy = new CounterStrategy();
    strategies.at(index)->~WarStrategy();
  }
  else
  {
    std::cout << "Bad input -> changeStrategy("+faction+","+strat+")" << std::endl;
    return;
  }
 strategies.at(index) = strategy;




}





