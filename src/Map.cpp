#include "Map.h"

Map::Map () {
	using std::calloc;
	size.x = 10; //temp
	size.y = 5;
	tiles = (Tile **) calloc (size.y, sizeof (Tile *));
	for (uint16_t y = 0; y < size.y; y++) {
		tiles[y] = new Tile[size.x];
		for (uint16_t x = 0; x < size.x; x++)
			tiles[y][x].setPos (x, y);
	}
}

Map::~Map () {
	for (uint16_t y = 0; y < size.y; y++)
		delete [] tiles[y];
	free (tiles);
}

void Map::draw () {
	glLineWidth (2.0);
	glEnableClientState (GL_VERTEX_ARRAY);
	for (uint16_t y = 0; y < size.y; y++)
		for (uint16_t x = 0; x < size.x; x++)
			tiles[y][x].draw ();
	glDisableClientState (GL_VERTEX_ARRAY);
}
