#include "SelectSimulation.h"

SelectSimulation::SelectSimulation(int simulation) : simulation(simulation) { }

void SelectSimulation::execute() {
	// Additional logic can be added here if desired
	WarEngine::instance()->selectSimulation(simulation);
	result = WarEngine::instance()->getStats();
}
