#pragma once

#include <GL/gl.h>
#include "exceptions.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

class Config {

public:
	Config ();

	struct {
		struct {
			int width, height;
		} screen;
		struct {
			GLdouble FOV;
		} cam;
	} config;
};