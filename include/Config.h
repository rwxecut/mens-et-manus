#pragma once

#include <GL/gl.h>
#include "exceptions.h"
#include "lua_overlay.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

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
};