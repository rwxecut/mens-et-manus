#include "auxiliary/game_lua.h"


namespace lua::game {

	int *routineID;

	void init (LuaFile *LF, WindowState *winState) {
		routineID = &(winState->routineID);

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
		*routineID = lua_arg_int (L, 1);
		return 0;
	}
}
