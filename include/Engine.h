#pragma once

#include "lib/nuklear/nuklear_common.h"
#include "Window.h"
#include "routines/Routine.h"

#include <memory>

class Engine {

	RoutineHandler routineHandler;

	void handleKeydown (SDL_Scancode scancode);

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
