#pragma once

#include <cstdint>
#include <SDL.h>
#include <GL/gl.h>
#include "geometry.h"

#include "Routine.h"
#include "windowState.h"

class MainMenu : public Routine {
public:
	MainMenu ();

	void update (WindowState *winState);
	void render ();
	void eventHandler (SDL_Event *event);
};
