#include "Tile.h"


Tile::Tile (point2d<uint16_t> pos, Texture *tex) {
	this->pos = pos;
	this->tex = tex;
}


point2d<int16_t> Tile::selected;


void Tile::draw () {
	GLfloat dy = pos.y * hex_l * 3 / 2;
	GLfloat dx = pos.x * 2 * hex_r + (pos.y & 1) * hex_r;
	//@formatter:off
	GLfloat vertex[] = {
			-hex_r + dx, -hex_l / 2 + dy, 0.f,
			 00.0f + dx, -hex_l     + dy, 0.f,
			 hex_r + dx, -hex_l / 2 + dy, 0.f,
			 hex_r + dx,  hex_l / 2 + dy, 0.f,
			 00.0f + dx,  hex_l     + dy, 0.f,
			-hex_r + dx,  hex_l / 2 + dy, 0.f};
	GLfloat texCoords[] = {
			-hex_r / 200 + 0.5f, 1 - (hex_l / 200 - 0.25f),
			           0 + 0.5f, 1 - 0,
			 hex_r / 200 + 0.5f, 1 - (hex_l / 200 - 0.25f),
			 hex_r / 200 + 0.5f, 1 - (hex_l / 200 + 0.25f),
			           0 + 0.5f, 1 - 1,
			-hex_r / 200 + 0.5f, 1 - (hex_l / 200 + 0.25f)};
	//@formatter:on
	glColor3fv ((pos == selected) ? colorSelected : colorUnselected);
	tex->draw (GL_POLYGON, 6, vertex, texCoords);
	glColor3fv (colorBorder);
	// Vertex pointer has already been set in tex->draw()
	glDrawArrays (GL_LINE_LOOP, 0, 6);
}
