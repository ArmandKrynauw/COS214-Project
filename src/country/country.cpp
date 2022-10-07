#include "country.h"

Country::Country(std::string name) : Party(name){}

int Country::getResourceCount(){

    return resourceCount;
}

int Country::setResourceCount(int resourceCount){
    
    this->resourceCount = resourceCount;
    return this->resourceCount;
}

//Throw exception
Alliance* Country::getAlliance(){

    return NULL;                
}

//Buy Troops and Place where necessary
void Country::makeDecision(){


}
//TUI prompts user to choose strategy for each theatre
void Country::chooseStrategy(){

    //Need to Notfy TUI that we need user input 
    //Recieve input and assign strategy for each theatre - input validation TUI side?
    //Thinking of using a mediator
    
    // for(Theatre * t : theatres)
    // {
    //     std::string input = someNotifyFunction();
    //     t->setStrategy(input);
    // }
}