#ifndef LOADDAYCOMMAND_H
#define LOADDAYCOMMAND_H

#include "WarCommand.h"

class LoadNextDay : public WarCommand {
	public:
		LoadNextDay();
		virtual void execute() override;
};

#endif // LOADDAYCOMMAND_H