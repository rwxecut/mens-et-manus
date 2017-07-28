#include <point.h>
#include "Tile.h"

GLfloat const Tile::hex_l = 100.0f;
GLfloat const Tile::hex_r = 86.6f;

void Tile::init (uint16_t x, uint16_t y) {
	pos.x = x;
	pos.y = y;
}

point<int16_t> Tile::selected;

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
	if ((pos.x == selected.x) && (pos.y == selected.y))
		glColor3f (0.3, 0.3, 0.3);
	else
		glColor3f (0.1, 0.1, 0.1);
	glDrawArrays (GL_POLYGON, 0, 6);
	glColor3f (0.1, 0.8, 0.8);
	glDrawArrays (GL_LINE_LOOP, 0, 6);
}