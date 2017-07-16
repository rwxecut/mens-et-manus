#pragma once

#include <stdexcept>
#include <sstream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>

#include "GameConfig.h"
#include "Map.h"
#include "Cam.h"
#include "Mouse.h"


class Game {
	SDL_GLContext context;
	SDL_Window *window;
	GameConfig const *gConf;

	Map map;
	Cam cam;
	Mouse mouse;

	void update ();
	void render ();
	void unproject (GLdouble srcX, GLdouble srcY,
	                GLdouble *objX, GLdouble *objY);
	void keyHandler ();
	void mousePositionHandler ();
	void mouseScrollHandler (int32_t delta);

public:
	Game (GameConfig const *config);
	~Game ();

	int mainLoop ();
};