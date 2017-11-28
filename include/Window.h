#pragma once

#include <cstdio>
#include <SDL.h>
#include <SDL_opengl.h>
#include "nuklear/nuklear_common.h"
#include "nk_lua.h"

#include "Config.h"
#include "geometry.h"
#include "Routine.h"
#include "windowState.h"

#include "Game.h"


class Window {

	WindowState winState;
	SDL_GLContext glContext;
	SDL_Window *sdlWindow;
	nk_context *nkContext;

	Game game;

	Routine* routine;

	uint32_t getFPS();

public:
	Window (Config *config);
	~Window ();

	int mainLoop ();
};
