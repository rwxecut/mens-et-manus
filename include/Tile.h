#pragma once

#include <GL/gl.h>
#include <cstdint>
#include "global.h"

class Tile {

public:
	static GLfloat const hex_l;
	static GLfloat const hex_r;
	upoint pos;
	static ipoint selected;

	void init (uint16_t x, uint16_t y);
	void draw ();
};

