#pragma once

#include <cstdio>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Game.h"
#include "Config.h"
#include "geometry.h"

class Window {

	SDL_GLContext glContext;
	SDL_Window *sdlWindow;

	Game game;
	Mouse mouse;

	struct {
		size2d<int> screenSize;
	} attrib;

	void update ();
	void render ();
	void keyHandler ();
	void mousePositionHandler ();
	void mouseScrollHandler (int32_t delta);

public:
	Window (Config *config);
	~Window ();

	int mainLoop ();
};
