#ifndef WARSTRATEGY_H
#define WARSTRATEGY_H

#include <string>

class WarStrategy {
protected:
    bool planned;
    std::string target;
    std::string type;

public:
    WarStrategy(std::string target);

    /**
     * Provides functionality to set whether this strategy is planned or not
     * @param p The bool value used to set Planned
    */

    void setPlanned(bool p);

    /**
     * Provides functionality to check whether this strategy was planned or not
     * @return bool : returns true if an attack was planned, else false
    */

    bool getPlanned();

    /**
     * Provides functionality to get the target of this strategy
     * @return string : the target of this strategy
    */

    std::string getTarget() const;

    /**
     * Provides functionality to get type of strategy
     * @return string : the type of strategy
    */

    std::string getType();

    /**
     * Executes  a strategy and generates modifiers based on opponents strategy
     * @param strat Opponents strategy to compare with
     * @return float : Modifier to be used in battles
    */

    virtual float executeStrategy(WarStrategy *strat) = 0;

    virtual ~WarStrategy();
};

#endif