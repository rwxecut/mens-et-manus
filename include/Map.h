#pragma once

#include <GL/gl.h>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <new>

#include "geometry.h"
#include "Tile.h"

class Map {
	friend class Game;

	Tile* tilesMem;
	Tile** tiles;

	size2d<uint16_t> size;

	static constexpr int mouseMoveArea = 40;

	void draw ();
	void getHoveredTile (point2d<GLdouble> point);

public:
	Map ();
	~Map ();
};
