#ifndef RETRIEVESIMULATIONS_H
#define RETRIEVESIMULATIONS_H

#include "WarCommand.h"

class RetrieveSimulations : public WarCommand {
   public:
    RetrieveSimulations();

    /**
     * Command the War Engine to provide a list of the available
     * simulations in the War Engine.
     */
    virtual void execute() override;

    virtual std::string getDescription() override;
};

#endif  // RETRIEVESIMULATIONS_H