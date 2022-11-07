#include "SelectSimulation.h"

SelectSimulation::SelectSimulation(int simulation) : simulation(simulation) { }

void SelectSimulation::execute() {
	// Additional logic can be added here if desired
	WarEngine::instance()->selectSimulation(simulation);
	result = WarEngine::instance()->getStats();
}

std::string SelectSimulation::getDescription() {
	return "Select Simulation - " + std::to_string(simulation);
}
