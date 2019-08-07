#pragma once

#include "lib/nuklear/nuklear_common.h"
#include "Window.h"
#include "Routine.h"
#include "routines/Splash.h"
#include "routines/MainMenu.h"
#include "routines/Game.h"

#include <memory>

class Engine {

	Splash *splash;
	MainMenu *mainMenu;
	Game *game;
	std::vector<Routine *> rTable;
	RoutineHandler routineHandler;

public:

	Window window;

	struct _SDL {
		_SDL ();
		~_SDL ();
	};
	using SDL = std::unique_ptr<_SDL>;
	SDL sdl;

	struct _Nuklear {
		nk_context *ctx;
		_Nuklear (Window &window);
		~_Nuklear ();
	};
	using Nuklear = std::unique_ptr<_Nuklear>;
	Nuklear nuklear;

	struct _Lua {
		_Lua (Window &window, Nuklear &nuklear, RoutineHandler &rHandler);
	};
	using Lua = std::unique_ptr<_Lua>;
	Lua lua;

	Engine ();
	~Engine ();

	int mainLoop ();
};
