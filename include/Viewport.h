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


class Viewport {
	SDL_GLContext context;
	SDL_Window *window;
	GameConfig const *gConf;

	Map map;
	Cam cam;
	Mouse mouse;

	void update ();
	void render ();
	void keyHandler ();
	void mousePositionHandler ();
	void mouseScrollHandler (int32_t delta);
	void mouseEventHandler (SDL_Event *event);
	void mouseCommonHander (); // Убрать если не нужно, см Viewport.cpp

public:
	Viewport (GameConfig const *config);
	~Viewport ();

	int mainLoop ();

	class SDL_Error;
	class GL_Error;
};