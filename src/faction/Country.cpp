#include "Country.h"

#include "../entity/product/Entity.h"
#include "../entity/product/Unit.h"
#include "../theatre/Theatre.h"

Country::Country(std::string name) : Faction(name) {
    armedForces["land"] = new ArmedForce("Army", "land");
    armedForces["sea"] = new ArmedForce("Navy", "sea");
    armedForces["air"] = new ArmedForce("Air Force", "air");
}

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

void Country::addEntity(Entity* entity) {
    if(resourceCount - entity->getValue() < 0) {
        throw WarException("Insufficient resources available.",
                           "insufficient_resources");
    }
    resourceCount -= entity->getValue();
    armedForces[entity->getType()]->add(entity);
    std::cout << "Adding: " << entity->getName() << std::endl;
}

void Country::removeEntity(Entity* entity) {
    if(entity) {
        armedForces[entity->getType()]->remove(entity);
    }
}

Entity* getEntity(int index) {}

// Buy Troops and Place where necessary
void Country::makeDecision() {}

// TUI prompts user to choose strategy for each theatre
void Country::chooseStrategy() {
    std::cout << this->getName() << " choosing strategies" << std::endl;

    // Need to Notify TUI that we need user input
    // Receive input and assign strategy for each theatre - input validation TUI
    // side? Thinking of using a mediator

    // for(Theatre * t : theatres)
    // {
    //     std::string input = someNotifyFunction();
    //     t->setStrategy(input);
    // }
}

json Country::getListOfUnits() {
    // json data = json{
    //     {"name", name},
    //     {"units", json::array()}
    // };

    // std::unordered_map<std::string, ArmedForce*>::iterator it;
    // for (it = armedForces.begin(); it != armedForces.end(); ++it) {

    // }
}

void Country::printUnits() {
    // int counter = 1;

    // for(Unit * u : units){
    //     std::cout<<counter<<". "<<u->getName()<<std::endl;
    //     counter++;
    // }
    // std::cout<<std::endl;
}