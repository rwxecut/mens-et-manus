#pragma once

#include <GL/gl.h>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "geometry.h"
#include "Tile.h"

class Map {
	friend class Game;

	std::vector<std::vector<Tile>> tiles;

	size2d<uint16_t> size;

	static constexpr int mouseMoveArea = 40;

	void draw ();
	void getHoveredTile (point2d<GLdouble> point);

public:
	Map ();
};
