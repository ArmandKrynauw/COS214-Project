#include "PlanStrategy.h"

PlanStrategy::PlanStrategy(){
}

float PlanStrategy::executeStrategy(WarStrategy* strat){
    setPlanned(true);
    return 1.3;
}

PlanStrategy::~PlanStrategy(){
}