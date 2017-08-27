#pragma once

#include <GL/gl.h>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include "point.h"
#include "Tile.h"

class Map {

public:
	Map ();
	~Map ();
	Tile **tiles;

	point2d<uint16_t> size;

	void draw ();
	void getHoveredTile (GLdouble x, GLdouble y);
};
