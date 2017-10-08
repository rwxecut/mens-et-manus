#pragma once

#include <cstdio>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Config.h"
#include "geometry.h"
#include "windowState.h"

#include "menus/MainMenu.h"
#include "Game.h"


class Window {

	WindowState winState;
	SDL_GLContext glContext;
	SDL_Window *sdlWindow;

	MainMenu menu;
	Game game;


	void update ();
	void render ();
	void eventHandler (SDL_Event *event);

public:
	Window (Config *config);
	~Window ();

	int mainLoop ();
};
