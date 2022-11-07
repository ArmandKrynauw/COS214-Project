#include "LoadDay.h"

LoadDay::LoadDay(int day) : day(day) {}

void LoadDay::execute() { 
	// Additional logic can be added here if desired
	WarEngine::instance()->loadSpecificBattleDay(day);
	result = WarEngine::instance()->getStats();
}

std::string LoadDay::getDescription() {
	return "Load Specific Battle Day - " + std::to_string(day);
}
