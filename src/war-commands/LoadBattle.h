#ifndef LOADBATTLECOMMAND_H
#define LOADBATTLECOMMAND_H

#include "WarCommand.h"

class LoadBattle : public WarCommand {
	public:
		LoadBattle();
		virtual void execute() override;
		virtual std::string getDescription() override;
};

#endif // LOADBATTLECOMMAND_H