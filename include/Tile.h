#pragma once

#include "lib/glad.h"
#include <cstdint>
#include "Texture.h"
#include "auxiliary/geometry.h"

class Tile {
	friend class Map;

	Texture *tex;

	static constexpr GLfloat hex_l = 100.0f;
	static constexpr GLfloat hex_r = 86.6f;

	//@formatter:off
	const GLfloat hexVertex[18] = {
			-hex_r, -hex_l / 2, 0,
			 0.00f, -hex_l,     0,
			 hex_r, -hex_l / 2, 0,
			 hex_r,  hex_l / 2, 0,
			 0.00f,  hex_l,     0,
			-hex_r,  hex_l / 2, 0
	};
	const GLfloat texCoords[12] = {
			-hex_r / 200 + 0.5f, 1 - (hex_l / 200 - 0.25f),
			 0.00f / 200 + 0.5f, 1 - 0,
			 hex_r / 200 + 0.5f, 1 - (hex_l / 200 - 0.25f),
			 hex_r / 200 + 0.5f, 1 - (hex_l / 200 + 0.25f),
			 0.00f / 200 + 0.5f, 1 - 1,
			-hex_r / 200 + 0.5f, 1 - (hex_l / 200 + 0.25f)
	};
	const GLfloat colorUnselected[3]  = {1.000, 1.000, 1.000};
	const GLfloat colorSelected[3]    = {0.122, 0.608, 0.176};
	const GLfloat colorBorder[3]      = {0.737, 0.737, 0.737};
	//@formatter:on

public:
	point2d<uint16_t> pos;

	static point2d<int16_t> selected;
	static point2d<int16_t> visBottomLeft, visTopRight;

	Tile (point2d<uint16_t> pos, Texture *tex);
	void draw ();
};
