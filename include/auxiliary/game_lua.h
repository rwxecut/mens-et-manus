#pragma once

#include "Routine.h"
#include "auxiliary/lua_overlay.h"


namespace lua::game {
	void init (lua_State *L, WindowState *winState);

	// Binded functions
	int switchRoutine (lua_State *L);
}
