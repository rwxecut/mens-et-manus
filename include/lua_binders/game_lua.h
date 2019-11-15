#pragma once

#include <SDL.h>
#include "LuaFile.h"
#include "routines/Routine.h"


namespace lua::game {
	void init (SDL_Window *window, RoutineHandler *routineHandler);
	void bind (LuaFile *LF);
}
