#pragma once

#include <GL/gl.h>
#include <cstdint>
#include "geometry.h"

class Tile {

public:
	static const GLfloat hex_l;
	static const GLfloat hex_r;
	point2d<uint16_t> pos;
	static point2d<int16_t> selected;

	void init (uint16_t x, uint16_t y);
	void draw ();
};
