#pragma once

#include "lib/glad.h"
#include <cstdint>
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
	point2d<int16_t> getHoveredTile (point2d<GLdouble> point);
	void setSelectedTile (point2d<int> mousePos);
	void setVisibleTiles (size2d<int> winSize);

public:
	Map ();
	~Map ();
};
