#pragma once

#include "lib/glad.h"
#include <vector>
#include <SDL.h>
#include "lib/nuklear/nuklear_common.h"

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
