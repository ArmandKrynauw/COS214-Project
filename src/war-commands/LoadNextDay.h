#ifndef LOADDAYCOMMAND_H
#define LOADDAYCOMMAND_H

#include "WarCommand.h"

class LoadNextDay : public WarCommand {
	public:
		LoadNextDay();

		/**
		 * Will load the next battle day of the current simulation running in
		 * the War Engine.
		*/
		virtual void execute() override;

		virtual std::string getDescription() override;
};

#endif // LOADDAYCOMMAND_H