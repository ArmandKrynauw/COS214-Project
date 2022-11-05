#include "WarCommand.h"

WarCommand::WarCommand() { }

nlohmann::json WarCommand::getResult() const {
	return result;
}

WarCommand::~WarCommand() { }
