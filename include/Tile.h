#pragma once

#include <GL/gl.h>
#include <cstdint>

class Tile {

public:
	static GLfloat const hex_l;
	static GLfloat const hex_r;
	struct {
		uint16_t x, y;
	} pos;

	void setPos (uint16_t x, uint16_t y);
	void draw ();
};

