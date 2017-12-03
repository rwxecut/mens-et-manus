#pragma once

#include <GL/gl.h>
#include "exceptions.h"
#include "auxiliary/lua_overlay.h"


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

	GLdouble fpsInterval;
};