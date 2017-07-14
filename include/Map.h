#pragma once

#include <GL/gl.h>
#include <cstdint>
#include <cstdlib>
#include "Tile.h"

class Map {

	Tile **tiles;

	struct {
		uint16_t x = 5, y = 10;
	} size; // temporary

public:
	Map ();
	~Map ();
	void draw ();
};
