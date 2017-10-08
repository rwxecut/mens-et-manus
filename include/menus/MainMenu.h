#pragma once

#include <cstdint>
#include <SDL.h>
#include <GL/gl.h>
#include "geometry.h"
#include "windowState.h"

class MainMenu {
public:
	MainMenu ();

	bool active = false;

	void eventHandler (SDL_Event *event);
	void update (WindowState *winState);
	void render ();
};
