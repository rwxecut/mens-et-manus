#pragma once

#include <stdio.h>
#include <stdexcept>
#include <sstream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>

#include "Map.h"
#include "Cam.h"
#include "Mouse.h"
#include "Config.h"
#include "point.h"


class Game {
	SDL_GLContext glContext;
	SDL_Window *window;

	Map map;
	Cam cam;
	Mouse mouse;

	struct {
		size2d<int> screenSize;
	} attrib;

	void update ();
	void render ();
	void unproject (GLdouble srcX, GLdouble srcY,
	                GLdouble *objX, GLdouble *objY);
	void keyHandler ();
	void mousePositionHandler ();
	void mouseScrollHandler (int32_t delta);

public:
	Game (Config *config);
	~Game ();

	int mainLoop ();
};