#ifndef LOADPREVIOUSDAY_H
#define LOADPREVIOUSDAY_H

#include "WarCommand.h"

class LoadPreviousDay : public WarCommand {
	public:
		LoadPreviousDay();
		virtual void execute() override;
		virtual std::string getDescription() override;
};

#endif // LOADPREVIOUSDAY_H