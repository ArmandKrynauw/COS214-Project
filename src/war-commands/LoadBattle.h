#ifndef LOADBATTLECOMMAND_H
#define LOADBATTLECOMMAND_H

#include "WarCommand.h"

class LoadBattle : public WarCommand {
   public:
    LoadBattle();

    /**
     * Load the battle day results of the current day and simulation
     * running in the War Engine.
     */
    virtual void execute() override;

    virtual std::string getDescription() override;
};

#endif  // LOADBATTLECOMMAND_H