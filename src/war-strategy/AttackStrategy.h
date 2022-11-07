#ifndef ATTACKSTRATEGY_H
#define ATTACKSTRATEGY_H

#include "WarStrategy.h"
/**
 * This class is a ConcreteState of the WarStrategy State Pattern Hierarchy. This state is used if a country wants
 * to attack on a battle day. If the current attack strategy was planned a country will have 1.5 times more damage else
 * the country will have the normal damage.
 */
class AttackStrategy : public WarStrategy {
    public:
        /**
         * Provides functionality to create a AttackStrategy object.
         * 
         * @param target Target of the strategy
         */
        AttackStrategy(std::string target);
        /**
         * Inherited function from WarStrategy.
         * If passed in WarStrategy was Planned
         * Modifier will be 1.5 else it will be 1.
         * 
         * @param strat WarStrategy object
         * @return float Modifier to be used in a battle
        */
        float executeStrategy(WarStrategy *strat);
         /**
         * Provide functionality to destroy a AttackStrategy object.
         */
        virtual ~AttackStrategy();
};

#endif // ATTACKSTRATEGY_H