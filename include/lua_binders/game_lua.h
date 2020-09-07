#pragma once

#include <SDL.h>
#include "lua_binders/bind_lua.h"
#include "routines/Routine.h"


namespace lua::bind {
	class Game : public Bind {
		static RoutineHandler *rHandler;
		static SDL_Window *sdlWindow;

	public:
		Game (File *LF);
		static void init (SDL_Window *window, RoutineHandler *routineHandler);

	/* Binded functions */
	private:
		static std::tuple<int, int> getScreenResolution ();
		static void switchRoutine (int routineID);
		static void applySettings ();
	};
}
