#include "auxiliary/game_lua.h"


namespace lua::game {

	int *routineID;

	void init (lua_State *L, WindowState *winState) {
		routineID = &(winState->routineID);

		// Bind functions
		luaL_Reg funclist[] = {
				lua_addBindFunc (switchRoutine),
				{NULL, NULL}
		};
		luaL_newlib (L, funclist);

		// Export constants
		field<int> keys[] = {
				lua_addExportKey (finalization),
				lua_addExportKey (gameRoutine),
				lua_addExportKey (mainMenuRoutine),
				{NULL, 0}
		};
		setTableFields (L, keys);
		lua_setglobal (L, "game");
	}


	// Binded functions

	int switchRoutine (lua_State *L) {
		*routineID = (int) luaL_checkinteger (L, 1);
		return 0;
	}
}
