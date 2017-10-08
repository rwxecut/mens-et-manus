#pragma once

#include <stdexcept>
#include <sstream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>

#include "Routine.h"
#include "windowState.h"
#include "Map.h"
#include "Cam.h"


class Game : public Routine {

	Map map;
	Cam cam;

	void unproject (point2d<GLdouble> source, point2d<GLdouble> *object);

	void keyHandler ();
	void mousePositionHandler (WindowState *winState);

public:
	Game (Config *config);

	void update (WindowState *winState);
	void render ();
	void eventHandler (SDL_Event *event);
};
