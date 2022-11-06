#ifndef RETRIEVESIMULATIONS_H
#define RETRIEVESIMULATIONS_H

#include "WarCommand.h"

class RetrieveSimulations : public WarCommand {
	public:
		RetrieveSimulations();
		virtual void execute() override;
		virtual std::string getDescription() override;
};

#endif // RETRIEVESIMULATIONS_H