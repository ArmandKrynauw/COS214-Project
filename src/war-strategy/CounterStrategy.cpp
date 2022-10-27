#include "CounterStrategy.h"
#include "PlanStrategy.h"

CounterStrategy::CounterStrategy(){

}

float CounterStrategy::executeStrategy(WarStrategy* strat){
    AttackStrategy* test = dynamic_cast<AttackStrategy*> (strat);
    if(test != nullptr && strat->getPlanned()){
        return 2.3;
    }
    else{
        return 0.7;
    }
}

CounterStrategy::~CounterStrategy(){
}