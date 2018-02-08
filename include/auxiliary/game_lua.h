#pragma once

#include "LuaFile.h"
#include "Routine.h"
#include "auxiliary/lua_overlay.h"


namespace lua::game {
	void init (LuaFile *LF, WindowState *winState);

	// Binded functions
	lua_cfunc (switchRoutine);
}
