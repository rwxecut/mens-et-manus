#pragma once

#include <SDL.h>
#include "windowState.h"

// Routines' IDs for Lua
enum {
	gameRoutine = 0,
	mainMenuRoutine = 1
};

class Routine {
public:
	virtual void update (WindowState *winState) = 0;
	virtual void render () = 0;
	virtual void eventHandler (SDL_Event *event) = 0;
};
