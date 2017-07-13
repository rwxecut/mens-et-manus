#pragma once

#include <GL/gl.h>
#include <cstdint>
#include <cstdlib>
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
};
