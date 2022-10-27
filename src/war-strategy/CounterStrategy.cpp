#include "CounterStrategy.h"
#include "PlanStrategy.h"

CounterStrategy::CounterStrategy(){

}

float CounterStrategy::executeStrategy(WarStrategy* strat){
    PlanStrategy* test = dynamic_cast<PlanStrategy*> (strat);
    if(test != nullptr && strat->getPlanned()){
        return 2.0;
    }
    else{
        return 0.7;
    }
}

CounterStrategy::~CounterStrategy(){
}