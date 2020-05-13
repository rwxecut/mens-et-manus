#include "lua_binders/game_lua.h"
#include <tuple>
#include "Config.h"


namespace lua {
	GameBinding::GameBinding (LuaFile *LF) : LF(LF)
	{
		// Usertype for game core functions bindings should not be directly used in scripts
		auto game = LF->state.new_usertype<GameBinding> ("__GameBindingType");
		/*---------- Export functions ----------*/
		#define GAME_EXPORT_METHOD(field) {game[#field] = &GameBinding::field;}
		GAME_EXPORT_METHOD (getScreenResolution);
		GAME_EXPORT_METHOD (switchRoutine);
		GAME_EXPORT_METHOD (applySettings);
		#undef GAME_EXPORT_METHOD

		/*---------- Export constants ----------*/
		#define GAME_EXPORT_CONSTANT(field) {game[#field] = sol::var(field);}
		GAME_EXPORT_CONSTANT (finalization);
		GAME_EXPORT_CONSTANT (gameRoutine);
		GAME_EXPORT_CONSTANT (mainMenuRoutine);
		#undef GAME_EXPORT_CONSTANT
	}

	void GameBinding::init (SDL_Window *window, RoutineHandler *routineHandler) {
		sdlWindow = window;
		rHandler = routineHandler;
	}

	RoutineHandler *GameBinding::rHandler;
	SDL_Window *GameBinding::sdlWindow;

	/*---------- Binded functions ----------*/

	std::tuple<int, int> GameBinding::getScreenResolution () {
		SDL_DisplayMode mode;
		int currDisplay = 0;
		SDL_GetCurrentDisplayMode (currDisplay, &mode);
		return std::make_tuple (mode.w, mode.h);
	}


	void GameBinding::switchRoutine (int routineID) {
		rHandler->new_id = (uint8_t) routineID;
	}


	void GameBinding::applySettings () {
		config.loadSettings ();
		SDL_SetWindowSize (sdlWindow, config.screen.size.width, config.screen.size.height);
		SDL_SetWindowFullscreen (sdlWindow, (config.screen.fullscreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
		SDL_SetWindowPosition (sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
}
