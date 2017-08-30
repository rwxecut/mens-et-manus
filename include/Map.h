#pragma once

#include <GL/gl.h>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "geometry.h"
#include "Tile.h"

class Map {

	std::vector<std::vector<Tile> > tiles;

public:
	Map ();

	size2d<uint16_t> size;

	void draw ();
	void getHoveredTile (GLdouble x, GLdouble y);
};
