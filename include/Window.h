#pragma once

#include <cstdio>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "nuklear/nuklear_common.h"
#include "auxiliary/game_lua.h"
#include "auxiliary/geometry.h"

#include "Config.h"
#include "Routine.h"
#include "windowState.h"

#include "MainMenu.h"
#include "Game.h"

extern int routineID;

class Window {

	WindowState winState;
	SDL_GLContext glContext;
	SDL_Window *sdlWindow;

	MainMenu mainMenu;
	Game game;

	Routine *routine;
	int currRoutineID;
	bool switchRoutine();

	uint32_t getFPS ();

public:
	Window (Config *config);
	~Window ();

	int mainLoop ();
};
