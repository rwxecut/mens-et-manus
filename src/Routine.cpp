#include <stdexcept>
#include "Routine.h"


void RoutineHandler::assignRoutinesTable (std::vector<Routine *> routineTable) {
	rTable = routineTable;
}


bool RoutineHandler::switchID () {
	if (rTable.at (id)) {
		routine = rTable.at (id);
		return true;
	}
	return false;
}


void RoutineHandler::update (WindowState *winState) {
	routine->update (winState);
}


void RoutineHandler::render () {
	routine->render ();
}


void RoutineHandler::eventHandler (SDL_Event *event) {
	routine->eventHandler (event);
}
