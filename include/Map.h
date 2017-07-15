#pragma once

#include <GL/gl.h>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include "Tile.h"

class Map {

	Tile **tiles;

	struct {
		uint16_t x, y;
	} size;

public:
	Map ();
	~Map ();

	void draw ();
	void getHoveredTile (GLdouble x, GLdouble y, int16_t *tileX, int16_t *tileY);
};
