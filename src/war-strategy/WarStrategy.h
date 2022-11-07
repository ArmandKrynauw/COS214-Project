#ifndef WARSTRATEGY_H
#define WARSTRATEGY_H

#include <string>
/**
 * This class is the AbstractState for the WarStrategy State Design Pattern
 * Hierarchy. This State pattern provides countries with different strategies to
 * use in theatres where each strategy has its advantages and disadvantages.
 */
class WarStrategy {
   protected:
    bool planned;
    std::string target;
    std::string type;

   public:
    /**
     * Provides functionality to create a WarStrategy object.
     *
     * @param target Target of the strategy
     */
    WarStrategy(std::string target);
    /**
     * Provides functionality to set planned variable
     *
     * @param p Value to set planned
     */
    void setPlanned(bool p);
    /**
     * Provides functionality to check whether this strategy was planned.
     *
     * @return true Return true if strategy was planned
     * @return false Return false if strategy was not planned
     */
    bool getPlanned();
    /**
     * Provides functionality to get the target of this strategy
     *
     * @return std::string Target of the strategy
     */
    std::string getTarget() const;
    /**
     * Provides functionality to get type of strategy
     *
     * @return string The type of strategy
     */
    std::string getType();
    /**
     * Pure virtual function to be implemented in the child classes.
     *
     * @param strat WarStrategy object
     * @return float Modifier to be used in a battle
     */
    virtual float executeStrategy(WarStrategy* strat) = 0;
    /**
     * Provides functionality to destroy a WarStrategy object.
     */
    virtual ~WarStrategy();
};

#endif