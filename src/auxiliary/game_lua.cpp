#include "auxiliary/game_lua.h"

#define GAME_ADD_FIELD(field) {game[#field] = field;}

namespace lua::game {
	RoutineHandler *rHandler;

	// Binded functions

	void switchRoutine (int routineID) {
		rHandler->id = (uint8_t) routineID;
	}


	// Bind functions
	void init (LuaFile *LF, RoutineHandler *routineHandler) {
		rHandler = routineHandler;

		sol::table game = LF->state.create_named_table ("game");
		// Bind functions
		GAME_ADD_FIELD (switchRoutine);

		// Export constants
		GAME_ADD_FIELD (finalization);
		GAME_ADD_FIELD (gameRoutine);
		GAME_ADD_FIELD (mainMenuRoutine);
	}

}
