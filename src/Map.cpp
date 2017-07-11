#include <GL/gl.h>
#include "Map.h"

Map::Map () {
	// Only wind and tumbleweed there...
}

void Map::draw () {
	// Draw hexagons (temp)
	glLineWidth (2.0);
	int hexnum = 5;
	GLfloat hex_l = 100.f;
	GLfloat hex_r = hex_l * 0.866f; // 3*sqrt(3)
	glEnableClientState (GL_VERTEX_ARRAY);
	for (int i = -hexnum; i <= hexnum; i++) {
		GLfloat dy = i * hex_l * 3 / 2;
		for (int j = -hexnum; j <= hexnum; j++) {
			GLfloat dx = j * 2 * hex_r + (i & 1) * hex_r;
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
	}
	glDisableClientState (GL_VERTEX_ARRAY);
}
