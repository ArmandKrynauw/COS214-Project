#include "RetrieveSimulations.h"

RetrieveSimulations::RetrieveSimulations() { }

void RetrieveSimulations::execute() {
	// Additional logic can be added here if desired
	result = WarEngine::instance()->getAvailableSimulations();
}
