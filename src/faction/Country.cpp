#include "Country.h"

Country::Country(std::string name) : Faction(name) {}

int Country::getResourceCount() {
    int resourceCount = baseResourceCount;
    return resourceCount;
}

void Country::setResourceCount(int baseResourceCount) {
    this->baseResourceCount = baseResourceCount;
}

Alliance* Country::getAlliance() { return NULL; }

// Buy Troops and Place where necessary
void Country::makeDecision() {}

// TUI prompts user to choose strategy for each theatre
void Country::chooseStrategy() {
    // Need to Notify TUI that we need user input
    // Receive input and assign strategy for each theatre - input validation TUI
    // side? Thinking of using a mediator

    // for(Theatre * t : theatres)
    // {
    //     std::string input = someNotifyFunction();
    //     t->setStrategy(input);
    // }
}