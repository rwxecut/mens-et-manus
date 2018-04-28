#pragma once

#include <GL/gl.h>
#include "LuaFile.h"
#include "Logger.h"


class Config {

public:
	Config ();

	struct {
		int width, height;
	} screen;

	struct {
		GLdouble moveSpeedMax, moveAcceleration;
		GLdouble zoomSpeed;
	} cam;

	GLdouble fpsMeasureInterval;
};