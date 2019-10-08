#include "Tile.h"


glm::ivec2 Tile::selected;
glm::ivec2 Tile::visBottomLeft, Tile::visTopRight;


const GLfloat Tile::hexVertex[24] = {
		//@formatter:off
		// X        Y                        S                             T
		 0.00f,   hex_l,         0.00f / (2 * hex_l) + 0.5f,  1,
		-hex_r,   hex_l / 2,     hex_r / (2 * hex_l) + 0.5f,  hex_l / (2 * hex_l) + 0.25f,
		-hex_r,  -hex_l / 2,     hex_r / (2 * hex_l) + 0.5f,  hex_l / (2 * hex_l) - 0.25f,
		 0.00f,  -hex_l,         0.00f / (2 * hex_l) + 0.5f,  0,
		 hex_r,  -hex_l / 2,    -hex_r / (2 * hex_l) + 0.5f,  hex_l / (2 * hex_l) - 0.25f,
		 hex_r,   hex_l / 2,    -hex_r / (2 * hex_l) + 0.5f,  hex_l / (2 * hex_l) + 0.25f
		//@formatter:on
};


Tile::Tile (glm::ivec2 pos, Texture *tex) {
	this->pos = pos;
	this->tex = tex;
}


void Tile::draw (ShaderProgram &shader, gl::Hex &hex) {
	GLfloat dy = pos.y * hex_l * 3 / 2;
	GLfloat dx = pos.x * 2 * hex_r + (pos.y & 1) * hex_r;
	shader.setUniform ("tilePos", glm::vec2 (dx, dy));
	// Draw tile
	shader.setUniform ("drawBorder", 0);
	hex.drawMode = GL_TRIANGLE_FAN;
	shader.setUniform ("tex", 0);
	tex->bind (0);
	shader.setUniform ("selected", (pos == selected));
	hex.draw ();
	// Draw border
	shader.setUniform ("drawBorder", 1);
	hex.drawMode = GL_LINE_LOOP;
	hex.draw ();
}
