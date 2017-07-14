#include "Save.h"
#include "Map.h"
#include "util.h"

Map::Map () {
	tiles = mem::new2DArray<Tile> (size.x, size.y);
	for (uint16_t y = 0; y < size.y; y++)
		for (uint16_t x = 0; x < size.x; x++) {}
}

Map::~Map () {
	mem::delete2DArray (tiles);
}

void Map::draw () {
	glLineWidth (2.0);
	glEnableClientState (GL_VERTEX_ARRAY);
	for (uint16_t y = 0; y < size.y; y++)
		for (uint16_t x = 0; x < size.x; x++)
			tiles[y][x].draw ();
	glDisableClientState (GL_VERTEX_ARRAY);
}
