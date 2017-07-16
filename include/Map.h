#pragma once

#include <GL/gl.h>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include "global.h"
#include "Tile.h"

class Map {

public:
	Map ();
	~Map ();
	Tile **tiles;

	upoint size;

	void draw ();
	void getHoveredTile (GLdouble x, GLdouble y, int16_t *tileX, int16_t *tileY);
};
