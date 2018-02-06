#include "Tile.h"


Tile::Tile (point2d<uint16_t> pos, Texture *tex) {
	this->pos = pos;
	this->tex = tex;
}


point2d<int16_t> Tile::selected;
point2d<int16_t> Tile::visBottomLeft, Tile::visTopRight;


void Tile::draw () {
	GLfloat dy = pos.y * hex_l * 3 / 2;
	GLfloat dx = pos.x * 2 * hex_r + (pos.y & 1) * hex_r;
	GLfloat vertex[18] = {0};
	moveVertexArray3d<GLfloat> (hexVertex, vertex, 6, dx, dy, 0);
	glColor3fv ((pos == selected) ? colorSelected : colorUnselected);
	tex->draw (GL_POLYGON, 6, vertex, texCoords);
	glColor3fv (colorBorder);
	// Vertex pointer has already been set in tex->draw()
	glDrawArrays (GL_LINE_LOOP, 0, 6);
}
