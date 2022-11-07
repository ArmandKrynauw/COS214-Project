#ifndef COUNTERSTRATEGY_H
#define COUNTERSTRATEGY_H

#include "WarStrategy.h"
/**
 * This class is a ConcreteState of the WarStrategy State Pattern Hierarchy.
 * This state is used if a country wants to counter on a battle day. A country
 * may have better damage when countering if the opposing country has a planned
 * attack strategy otherwise the country will provide less that usual damage.
 */
class CounterStrategy : public WarStrategy {
   public:
    /**
     * Provides functionality to create a CounterStrategy object.
     *
     * @param target Target of the strategy
     */
    CounterStrategy(std::string target);
    /**
     * Inherited function from WarStrategy.
     * If passed in WarStrategy has a type of "Attack" and was Planned
     * Modifier will be 2.8 else it will be 0.7.
     *
     * @param strat WarStrategy object
     * @return float Modifier to be used in a battle
     */
    float executeStrategy(WarStrategy* strat);
    /**
     * Provide functionality to destroy a CounterStrategy object.
     */
    virtual ~CounterStrategy();
};
#endif  // COUNTERSTRATEGY_H