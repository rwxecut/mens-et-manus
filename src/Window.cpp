#include "Window.h"
#include <cstdio>
#include <SDL_image.h>
#include "auxiliary/geometry.h"
#include "auxiliary/errors.h"
#include "Logger.h"
#include "Config.h"


Window::Window () {
	// Load attributes from config
	fpsMeasureInterval = config.fpsMeasureInterval * 1000;
	bool fullscreen = config.screen.fullscreen;

	// Create window
	sdlWindow = SDL_CreateWindow ("Mens et Manus",
	                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                              config.screen.size.width, config.screen.size.height,
	                              SDL_WINDOW_OPENGL | (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
	if (!sdlWindow)
		fatalError ("Window could not be created!");
	logger.write ("Window created");
}


Window::~Window () {
	if (sdlWindow) SDL_DestroyWindow (sdlWindow);
}


void Window::render () {
	SDL_GL_SwapWindow (sdlWindow);
	// Write FPS to window title or log
	writeFPS ();
}


size_t Window::getFPS (float *average) {
	static size_t FPS = 0;
	static size_t frames = 0;
	static uint32_t lasttime = SDL_GetTicks ();

	static uint64_t ticks = 0;
	static float averageFPS = 0;

	frames++;
	if (lasttime < SDL_GetTicks () - fpsMeasureInterval) {
		lasttime = SDL_GetTicks ();
		FPS = frames;
		frames = 0;

		if (average) {
			averageFPS = averageFPS * (ticks / (ticks + 1.0f)) + FPS / (ticks + 1.0f);
			ticks++;
		}
	}

	if (average)
		*average = averageFPS;
	return FPS;
}


void Window::switchFPSMeasure () {
	averageEnabled = !averageEnabled;
	averageSwitched = true;
}


void Window::writeFPS () {
	size_t FPS = 0;
	static float avFPS = 0;
	char fpsStr[64] = {0};

	if (averageEnabled) {
		if (averageSwitched)
			logger.write ("Started measuring average FPS");
		FPS = getFPS (&avFPS);
		snprintf (fpsStr, sizeof (fpsStr), "Mens et Manus [FPS: %zu] [Average: %g]", FPS, avFPS);
	} else {
		if (averageSwitched) {
			logger.write ("Stopped measuring average FPS: %g", avFPS);
			avFPS = 0;
		}
		FPS = getFPS (nullptr);
		snprintf (fpsStr, sizeof (fpsStr), "Mens et Manus [FPS: %zu]", FPS);
	}
	averageSwitched = false;

	SDL_SetWindowTitle (sdlWindow, fpsStr);
}


void Window::switchWireframeMode () {
	static bool wireframeEnabled = false;

	wireframeEnabled = !wireframeEnabled;
	glPolygonMode (GL_FRONT_AND_BACK, wireframeEnabled ? GL_LINE : GL_FILL);
}
