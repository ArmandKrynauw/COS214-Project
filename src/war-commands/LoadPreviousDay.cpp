#include "LoadPreviousDay.h"

LoadPreviousDay::LoadPreviousDay() {}

void LoadPreviousDay::execute() {
	// Additional logic can be added here if desired
	WarEngine::instance()->loadPreviousBattleDay();
	result = WarEngine::instance()->getStats();
}
