#pragma once

#include <GL/gl.h>
#include <cstdint>
#include "geometry.h"

class Tile {

public:
	static constexpr GLfloat hex_l = 100.0f;
	static constexpr GLfloat hex_r = 86.6f;

	//@formatter:off
	const GLfloat colorUnselected[3] = {0.184, 0.518, 0.224};
	const GLfloat colorSelected[3]   = {0.122, 0.608, 0.176};
	const GLfloat colorBorder[3]     = {0.737, 0.737, 0.737};
	//@formatter:on

	point2d<uint16_t> pos;
	static point2d<int16_t> selected;

	Tile (point2d<uint16_t> _pos);
	void draw ();
};
