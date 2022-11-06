#ifndef LOADDAY_H
#define LOADDAY_H

#include "WarCommand.h"

class LoadDay : public WarCommand {
	public:
		LoadDay(int day);
		virtual void execute() override;
		virtual std::string getDescription() override;

	private:
		int day;
};

#endif // LOADDAY_H