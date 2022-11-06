#ifndef WARCOMMAND_H
#define WARCOMMAND_H

#include "../engine/WarEngine.h"
#include "../utilities/json.hpp"

class WarCommand {
	public:
		virtual void execute() = 0;
		virtual std::string getDescription() = 0;
		nlohmann::json getResult() const;
		virtual ~WarCommand();

	protected:
		nlohmann::json result;
		WarCommand();
};

#endif // WARCOMMAND_H