#pragma once

#include "lib/glad.h"
#include <vector>
#include <SDL.h>
#include "lib/nuklear/nuklear_common.h"

#include "Routine.h"
#include "routines/Splash.h"
#include "routines/MainMenu.h"
#include "routines/Game.h"


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
	bool averageEnabled = false, averageSwitched = false;
	size_t getFPS (float *average);
	void writeFPS ();

	void switchWireframeMode ();

public:
	Window ();
	~Window ();

	int mainLoop ();
};
