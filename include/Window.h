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
	struct Mouse {
		point2d<int> pos;
		void positionHandler (Window* window);
		void scrollHandler (Window* window, int32_t delta);
	} mouse;

	struct {
		size2d<int> screenSize;
	} attrib;

	void update ();
	void render ();
	void keyHandler ();

public:
	Window (Config *config);
	~Window ();

	int mainLoop ();
};
