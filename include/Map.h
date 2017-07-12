#pragma once

#include <GL/gl.h>
#include <cstdint>
#include <cstdlib>

class Tile {
	static GLfloat const hex_l;
	static GLfloat const hex_r;

	struct {
		int16_t x, y;
	} pos;

public:
	Tile (uint16_t posx, uint16_t posy);

	void draw ();
};


class Map {

	Tile ***tiles;

	struct {
		uint16_t x, y;
	} size;

public:
	Map ();
	~Map ();

	void draw ();
};
