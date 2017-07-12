#include "Map.h"

Map::Map () {
	using std::calloc;
	size.x = 10; //temp
	size.y = 5;
	tiles = (Tile ***) calloc (size.y, sizeof (Tile **));
	for (uint16_t y = 0; y < size.y; y++) {
		tiles[y] = (Tile **) calloc (size.x, sizeof (Tile *));
		for (uint16_t x = 0; x < size.x; x++)
			tiles[y][x] = new Tile (x, y);
	}
}

Map::~Map () {
	for (uint16_t y = 0; y < size.y; y++) {
		for (uint16_t x = 0; x < size.x; x++)
			delete tiles[y][x];
		free (tiles[y]);
	}
	free (tiles);
}

void Map::draw () {
	glLineWidth (2.0);
	glEnableClientState (GL_VERTEX_ARRAY);
	for (uint16_t y = 0; y < size.y; y++)
		for (uint16_t x = 0; x < size.x; x++)
			tiles[y][x]->draw ();
	glDisableClientState (GL_VERTEX_ARRAY);
}

GLfloat const Tile::hex_l = 100.0f;
GLfloat const Tile::hex_r = 86.6f;

Tile::Tile (uint16_t posx, uint16_t posy) {
	pos.x = posx;
	pos.y = posy;
}

void Tile::draw () {
	GLfloat dy = pos.y * hex_l * 3 / 2;
	GLfloat dx = pos.x * 2 * hex_r + (pos.y & 1) * hex_r;
	// @formatter:off
	GLfloat vertices[] = {  -hex_r + dx, -hex_l/2 + dy, 0.f,
							 00.0f + dx, -hex_l   + dy, 0.f,
							 hex_r + dx, -hex_l/2 + dy, 0.f,
							 hex_r + dx,  hex_l/2 + dy, 0.f,
							 00.0f + dx,  hex_l   + dy, 0.f,
							-hex_r + dx,  hex_l/2 + dy, 0.f};
	// @formatter:on
	glVertexPointer (3, GL_FLOAT, 0, vertices);
	glColor3f (0.1, 0.1, 0.1);
	glDrawArrays (GL_POLYGON, 0, 6);
	glColor3f (0.1, 0.8, 0.8);
	glDrawArrays (GL_LINE_LOOP, 0, 6);
}

