#include "Map.h"


Map::Map () {
	size = {20, 10}; // temp
	tiles = (Tile **) calloc (size.height, sizeof (Tile *));
	tilesMem = (Tile *) calloc (size.width * size.height, sizeof (Tile));
	for (uint16_t y = 0; y < size.height; y++) {
		tiles[y] = tilesMem + y * size.width;
		for (uint16_t x = 0; x < size.width; x++)
			new (&tiles[y][x]) Tile ({x, y});
	}
}


Map::~Map () {
	free (tiles);
	free (tilesMem);
}


void Map::draw () {
	glLineWidth (2.0);
	glEnableClientState (GL_VERTEX_ARRAY);
	for (uint16_t y = 0; y < size.height; y++)
		for (uint16_t x = 0; x < size.width; x++)
			tiles[y][x].draw ();
	glDisableClientState (GL_VERTEX_ARRAY);
	glColor3f (1, 1, 1); // reset color
}


void Map::getHoveredTile (point2d<GLdouble> point) {
	struct {
		int16_t x; // Coordinates of centers
		int16_t y; // of the two nearest tiles
		GLdouble dist; // Distance from point to tile center
	} tCntr[2];

	// Coordinates of the point in the tiles coordinate system
	GLdouble x_hex = point.x / Tile::hex_r;
	GLdouble y_hex = point.y / (Tile::hex_l * 3 / 2);

	// Choose the nearest tiles
	int16_t y_floor = (int16_t) std::floor (y_hex);
	tCntr[0].x = (int16_t) std::floor (x_hex);
	tCntr[1].x = (int16_t) std::ceil (x_hex);
	if ((tCntr[0].x & 1) == (y_floor & 1)) { // Check parity
		tCntr[0].y = (int16_t) std::floor (y_hex);
		tCntr[1].y = (int16_t) std::ceil (y_hex);
	} else {
		tCntr[0].y = (int16_t) std::ceil (y_hex);
		tCntr[1].y = (int16_t) std::floor (y_hex);
	}

	// Calculate distance to the nearest tile center
	for (int i = 0; i <= 1; i++) {
		GLdouble dist_x = point.x - tCntr[i].x * Tile::hex_r;
		GLdouble dist_y = point.y - tCntr[i].y * Tile::hex_l * 3 / 2;
		tCntr[i].dist = std::sqrt (dist_x * dist_x + dist_y * dist_y);
	}

	// Return the nearest tile center
	int nearest = tCntr[0].dist >= tCntr[1].dist;
	Tile::selected.x = tCntr[nearest].x >> 1;
	Tile::selected.y = tCntr[nearest].y;
}
