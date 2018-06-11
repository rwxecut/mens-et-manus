#include <Config.h>
#include "auxiliary/game_lua.h"

#define GAME_ADD_FIELD(field) {game[#field] = field;}

namespace lua::game {
	RoutineHandler *rHandler;
	Config *cfg;
	SDL_Window *sdlWindow;
	void init (Config *config, SDL_Window *window, RoutineHandler *routineHandler) {
		rHandler = routineHandler;
		cfg = config;
		sdlWindow = window;
	}

	// Binded functions

	void switchRoutine (int routineID) {
		rHandler->id = (uint8_t) routineID;
	}


	void applySettings () {
		cfg->loadSettings ();
		SDL_SetWindowSize (sdlWindow, cfg->screen.width, cfg->screen.height);
		SDL_SetWindowFullscreen (sdlWindow, (cfg->screen.fullscreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
		SDL_SetWindowPosition (sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}

	// Bind functions
	void bind (LuaFile *LF) {
		sol::table game = LF->state.create_named_table ("game");
		// Bind functions
		GAME_ADD_FIELD (switchRoutine);
		GAME_ADD_FIELD (applySettings);

		// Export constants
		GAME_ADD_FIELD (finalization);
		GAME_ADD_FIELD (gameRoutine);
		GAME_ADD_FIELD (mainMenuRoutine);
	}

}
