#pragma once

#include <stdexcept>
#include <sstream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>

#include "Map.h"
#include "Cam.h"
#include "Mouse.h"


class Game {

	Map map;
	Cam cam;

	void unproject (GLdouble srcX, GLdouble srcY,
	                GLdouble *objX, GLdouble *objY);

public:
	Game (Config *config);
	void keyHandler (const uint8_t *keystates);
	void mouseScrollHandler (int32_t delta);
	void mousePositionHandler (int scrWidth, int scrHeight, int mouseX, int mouseY);
	void update (int mouseX, int mouseY);
	void render ();
};