#pragma once

#include <SDL.h>
#include "LuaFile.h"
#include "routines/Routine.h"


namespace lua {
	namespace bind {

		class Game {
			LuaFile *LF;
			static RoutineHandler *rHandler;
			static SDL_Window *sdlWindow;

		public:
			Game (LuaFile *LF);
			static void init (SDL_Window *window, RoutineHandler *routineHandler);

			/* Binded functions */
		private:
			static std::tuple<int, int> getScreenResolution ();
			static void switchRoutine (int routineID);
			static void applySettings ();
		};

	}
}
