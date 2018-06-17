#pragma once

#include <cstdio>
#include <vector>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "nuklear/nuklear_common.h"
#include "lua_binders/game_lua.h"
#include "lua_binders/nk_lua.h"
#include "auxiliary/geometry.h"

#include "auxiliary/errors.h"
#include "Logger.h"
#include "Config.h"
#include "Routine.h"

#include "Splash.h"
#include "MainMenu.h"
#include "Game.h"


class Window {

	SDL_GLContext glContext;
	SDL_Window *sdlWindow;
	nk_context *nkContext;

	Splash *splash;
	MainMenu *mainMenu;
	Game *game;
	std::vector<Routine *> rTable;
	RoutineHandler routineHandler;

	GLdouble fpsMeasureInterval;
	uint32_t getFPS ();

public:
	Window ();
	~Window ();

	int mainLoop ();
};
