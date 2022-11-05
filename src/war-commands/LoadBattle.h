#ifndef LOADBATTLECOMMAND_H
#define LOADBATTLECOMMAND_H

#include "WarCommand.h"

class LoadBattle : public WarCommand {
	public:
		LoadBattle();
		virtual void execute() override;
};

#endif // LOADBATTLECOMMAND_H