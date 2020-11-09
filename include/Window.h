#pragma once

#include "lib/glad.h"
#include <vector>
#include <SDL.h>
#include "lib/nuklear/nuklear_common.h"


class Window {

	SDL_Window *sdlWindow;

	GLdouble fpsMeasureInterval;
	bool averageEnabled = false, averageSwitched = false;
	size_t getFPS (float *average);
	void writeFPS ();

public:
	Window ();
	~Window ();

	SDL_Window *get () { return sdlWindow; }
	void render ();
	void switchFPSMeasure ();
	void switchWireframeMode ();
};
