#include "lua_binders/game_lua.h"
#include <tuple>

#define GAME_ADD_FIELD(field) {game[#field] = field;}

namespace lua::game {
	RoutineHandler *rHandler;
	SDL_Window *sdlWindow;


	void init (SDL_Window *window, RoutineHandler *routineHandler) {
		rHandler = routineHandler;
		sdlWindow = window;
	}

	// Binded functions


	std::tuple<int, int> getScreenResolution () {
		SDL_DisplayMode mode;
		int currDisplay = 0;
		SDL_GetCurrentDisplayMode (currDisplay, &mode);
		return std::make_tuple (mode.w, mode.h);
	};


	void switchRoutine (int routineID) {
		rHandler->id = (uint8_t) routineID;
	}


	void applySettings () {
		config.loadSettings ();
		SDL_SetWindowSize (sdlWindow, config.screen.size.width, config.screen.size.height);
		SDL_SetWindowFullscreen (sdlWindow, (config.screen.fullscreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
		SDL_SetWindowPosition (sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}


	// Bind
	void bind (LuaFile *LF) {
		sol::table game = LF->state.create_named_table ("game");
		/*---------- Export functions ----------*/
		GAME_ADD_FIELD (getScreenResolution);
		GAME_ADD_FIELD (switchRoutine);
		GAME_ADD_FIELD (applySettings);

		/*---------- Export constants ----------*/
		GAME_ADD_FIELD (finalization);
		GAME_ADD_FIELD (gameRoutine);
		GAME_ADD_FIELD (mainMenuRoutine);
	}

}
