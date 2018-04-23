#include "auxiliary/game_lua.h"


namespace lua::game {
	RoutineHandler *rHandler;

	void init (LuaFile *LF, RoutineHandler *routineHandler) {
		rHandler = routineHandler;

		// Bind functions
		luaL_Reg funclist[] = {
				lua_addBindFunc (switchRoutine),
				{NULL, NULL}
		};
		luaL_newlib (LF->L, funclist);

		// Export constants
		field<int> keys[] = {
				lua_addExportKey (finalization),
				lua_addExportKey (gameRoutine),
				lua_addExportKey (mainMenuRoutine),
				{NULL, 0}
		};
		setTableFields (LF->L, keys);
		lua_setglobal (LF->L, "game");
	}


	// Binded functions

	lua_cfunc (switchRoutine) {
		rHandler->id = lua_arg_int (L, 1);
		return 0;
	}
}
