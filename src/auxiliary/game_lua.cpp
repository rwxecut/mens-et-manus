#include "auxiliary/game_lua.h"


namespace lua::game {
	RoutineHandler *rHandler;


	void init (LuaFile *LF, RoutineHandler *routineHandler) {
		rHandler = routineHandler;

		sol::table game = LF->state.create_named_table ("game");
		// Bind functions
		game["switchRoutine"] = switchRoutine;

		// Export constants
		game["finalization"] = finalization;
		game["gameRoutine"] = gameRoutine;
		game["mainMenuRoutine"] = mainMenuRoutine;
	}


	// Binded functions

	void switchRoutine (int routineID) {
		rHandler->id = (uint8_t) routineID;
	}
}
