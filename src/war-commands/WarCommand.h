#ifndef WARCOMMAND_H
#define WARCOMMAND_H

#include "../engine/WarEngine.h"
#include "../utilities/json.hpp"

class WarCommand {
	public:
		virtual ~WarCommand();
		virtual void execute() = 0;
		nlohmann::json getResult() const;

	protected:
		nlohmann::json result;
		WarCommand();
};

#endif // WARCOMMAND_H