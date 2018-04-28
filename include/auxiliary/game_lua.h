#pragma once

#include "LuaFile.h"
#include "Routine.h"


namespace lua::game {
	void init (LuaFile *LF, RoutineHandler *routineHandler);

	// Binded functions
	void switchRoutine (int routineID);
}
