#include "Country.h"
#include "../entity/product/Unit.h"
Country::Country(std::string name) : Faction(name) {}

void Country::generateResources() {
    // TODO: Calculate newly generated resources by adding boosts provided by
    // mobilization to current resources.
    resourceCount += baseResourceCount + 0;
}

int Country::getResourceCount() {
    return resourceCount;
}

void Country::setBaseResourceCount(int baseResourceCount) {
    this->baseResourceCount = baseResourceCount;
}

int Country::getAttackPower(Theatre* theatre) {
    // Search through theatres that country is battling
    // Sum attack power of army in that specific theatre
    return 10;
}

Alliance* Country::getAlliance() {
    return NULL;
}

void Country::addUnit(Unit* unit) {
    // TODO: Subtract Unit Cost from resource count. If resource count is less
    // cost throw exception.

    // if (true) {
    //     throw WarException("Insufficient resources available.",
    //     "insufficient-resources");
    // }

    units.push_back(unit);
}

void Country::removeUnit(Unit* unit) {
    for (int i = 0; i < units.size(); i++) {
        if (units[i] == unit) {
            units.erase(units.begin() + i);
        }
    }
}

// Buy Troops and Place where necessary
void Country::makeDecision() {}

// TUI prompts user to choose strategy for each theatre
void Country::chooseStrategy() {
    std::cout <<this->getName() << " choosing strategies" << std::endl;
    // Need to Notify TUI that we need user input
    // Receive input and assign strategy for each theatre - input validation TUI
    // side? Thinking of using a mediator

    // for(Theatre * t : theatres)
    // {
    //     std::string input = someNotifyFunction();
    //     t->setStrategy(input);
    // }
}

void Country::printUnits(){
    // for(Unit * u : units){
    //     std::cout<<u->getName()<<std::endl;
    // }
}