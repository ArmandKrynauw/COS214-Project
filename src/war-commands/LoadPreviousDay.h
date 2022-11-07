#ifndef LOADPREVIOUSDAY_H
#define LOADPREVIOUSDAY_H

#include "WarCommand.h"

class LoadPreviousDay : public WarCommand {
	public:
		LoadPreviousDay();

		/**
		 * Load the previous battle day of the current simulation running in
		 * the War Engine.
		*/
		virtual void execute() override;

		virtual std::string getDescription() override;
};

#endif // LOADPREVIOUSDAY_H