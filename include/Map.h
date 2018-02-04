#pragma once

#include <GL/gl.h>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <new>

#include "auxiliary/geometry.h"
#include "Tile.h"
#include "Texture.h"

class Map {
	friend class Game;

	Tile *tilesMem;
	Tile **tiles;
	size2d<uint16_t> size;

	static constexpr int mouseMoveArea = 40;

	Texture *grassTex;

	void draw ();
	void getHoveredTile (point2d<GLdouble> point);

public:
	Map ();
	~Map ();
};
