#ifndef SELECTSIMULATION_H
#define SELECTSIMULATION_H

#include "WarCommand.h"

class SelectSimulation : public WarCommand {
   public:
    SelectSimulation(int simulation);

    /**
     * Selects a specific simulation in the War Engine to be run.
     */
    virtual void execute() override;

    virtual std::string getDescription() override;

   private:
    int simulation;
};

#endif  // SELECTSIMULATION_H