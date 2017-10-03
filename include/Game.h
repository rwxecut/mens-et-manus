#pragma once

#include <stdexcept>
#include <sstream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>

#include "Map.h"
#include "Cam.h"

class Game {
	friend class Window;

	Map map;
	Cam cam;

	void unproject (point2d<GLdouble> source, point2d<GLdouble> *object);

	void keyHandler (const uint8_t *keystates);
	void mousePositionHandler (size2d<int> screenSize, point2d<int> mousePos);
	void mouseScrollHandler (int32_t delta);
	void update (point2d<int> mousePos);
	void render ();

public:
	Game (Config *config);
};