#include "LoadBattle.h"

LoadBattle::LoadBattle() {}

void LoadBattle::execute() {
	// Additional logic can be added here if desired
	WarEngine::instance()->loadBattleDayResults();
	result = WarEngine::instance()->getStats();
}

std::string LoadBattle::getDescription() {
	return "Load Battle Day Results";
}
