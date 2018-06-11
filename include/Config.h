#pragma once

#include <GL/gl.h>
#include "auxiliary/util.h"
#include "LuaFile.h"
#include "Logger.h"


struct Config {
	void load ();
	void loadConfig ();
	void loadSettings ();

	struct {
		size2d<int> size;
		bool fullscreen;
	} screen;

	struct {
		GLdouble moveSpeedMax, moveAcceleration;
		GLdouble zoomSpeed;
	} cam;

	GLdouble fpsMeasureInterval;
};

#ifndef CONFIG_IMPLEMENT
extern Config config;
#endif
