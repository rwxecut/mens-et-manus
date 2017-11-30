#pragma once

#include "Routine.h"
#include "lua_overlay.h"


namespace lua::game {
	void init (lua_State *L);

	// Binded functions
	int switchRoutine (lua_State *L);
}
