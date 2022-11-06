#include "LoadNextDay.h"

LoadNextDay::LoadNextDay() {}

void LoadNextDay::execute() {
	// Additional logic can be added here if desired
	WarEngine::instance()->loadNextBattleDay();
	result = WarEngine::instance()->getStats();
}

std::string LoadNextDay::getDescription() {
	return "Load Next Battle Day";
}
