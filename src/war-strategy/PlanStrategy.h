#ifndef PLANSTRATEGY_H
#define PLANSTRATEGY_H

#include "WarStrategy.h"
/**
 * This class is a ConcreteState of the WarStrategy State Pattern Hierarchy.
 * This state is used if a country wants to plan on a battle day. The strategy
 * will set the planned variable to true and the country will receive the normal
 * damage modifier of 1.0.
 */
class PlanStrategy : public WarStrategy {
   public:
    /**
     * Provides functionality to create a PlanStrategy object.
     *
     * @param target Target of the strategy
     */
    PlanStrategy(std::string target);
    /**
     * Inherited function from WarStrategy.
     * It will set the strategy state to true and return a modifier of 1.0.
     *
     * @param strat WarStrategy object
     * @return float Modifier to be used in a battle
     */
    float executeStrategy(WarStrategy* strat);
    /**
     * Provide functionality to destroy a PlanStrategy object.
     */
    virtual ~PlanStrategy();
};
#endif  // PLANSTRATEGY_H