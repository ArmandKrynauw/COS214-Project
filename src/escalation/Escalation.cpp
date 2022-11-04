#include "Escalation.h"
#include "MiddleStage.h"
#include "LateStage.h"
#include "EarlyStage.h"

Escalation::Escalation(std::string stage) {
    state = stage;
}

Escalation * Escalation::checkStageOfWar(std::string stage) {
    if(stage=="Initial Stage"){
        return new EarlyStage(stage);
    } 
    
    if (stage == "EarlyStage") {
        return new EarlyStage(stage);
    }
    if (stage == "MiddleStage") {
        return new MiddleStage();
    } else if (stage == "LateStage") {
        return new LateStage();
    }
}

Escalation::~Escalation() {

}