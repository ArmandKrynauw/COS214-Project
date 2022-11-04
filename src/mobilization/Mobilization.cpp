#include "Mobilization.h"
#include "WarEconomy.h"
#include "TotalMobilization.h"
#include "PartialMobilization.h"
Mobilization::Mobilization(std::string state){
    this->state = state;
}

Mobilization::~Mobilization() {

}

Mobilization *  Mobilization::checkWarState(std::string warState, std::string newMobilization){
    if(warState == "Initial Stage"){
        return this;
    }
    else if(warState == "EarlyStage"){
            if(newMobilization == "TotalMobilization"){
                return this;
            }
            if(newMobilization == "PartialMobilization"){
                return  new PartialMobilization("PartialMobilization");
            }
            else if(newMobilization == "WarEconomy"){
                return new WarEconomy("WarEconomy");
            }
        
    }
    else if(warState == "MiddleStage"){
        if(newMobilization == "PartialMobilization"){
            return this;
        }
        if(newMobilization == "WarEconomy"){
            return new WarEconomy("WarEconomy");
        }
        else if(newMobilization == "TotalMobilization"){
            return new TotalMobilization("TotalMobilization");
        }
    }
    else if(warState == "LateStage"){
            if(this->state == "PartialMobilization" && newMobilization == "PartialMobilization"){
                return this;
            }
            else if((this->state == "WarEconomy" || this->state == "TotalMobilization") && newMobilization == "PartialMobilization"){
                return new PartialMobilization("PartialMobilization");
            }
            else if((this->state == "TotalMobilization" || this->state == "WarEconomy") && newMobilization == "WarEconomy"){
                return new WarEconomy("WarEconomy");
            }
            else if(this->state == "TotalMobilization" && newMobilization == "TotalMobilization"){
                return this;
            }

            
    }
    else{
        throw WarException("mobilization-not-found");
    }
    return new PartialMobilization("PartialMobilization");
    
}

void Mobilization::setState(std::string state){
    this->state = state;
}