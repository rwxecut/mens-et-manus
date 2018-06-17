#pragma once

#include <SDL.h>
#include "LuaFile.h"
#include "Config.h"
#include "Routine.h"


namespace lua::game {
	void init (SDL_Window *window, RoutineHandler *routineHandler);
	void bind (LuaFile *LF);
}
