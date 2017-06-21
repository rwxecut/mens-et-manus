#include <GL/gl.h>
#include <math.h>
#include "GameConfig.h"

extern GameConfig const *GCONF;

namespace map {
	void Draw () {
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();
		glTranslatef (GCONF->screen.width / 2.f, GCONF->screen.height / 2.f, 0.f);
		// @formatter:off
		GLfloat vertices[] = {	-100.f, -050.f,  000.f,
								 000.f, -100.f,  000.f,
								 100.f, -050.f,  000.f,
								 100.f,  050.f,  000.f,
								 000.f,  100.f,  000.f,
								-100.f,  050.f,  000.f};
		// @formatter:on
		glEnableClientState (GL_VERTEX_ARRAY);
		glVertexPointer (3, GL_FLOAT, 0, vertices);
		glDrawArrays (GL_POLYGON, 0, 6);
		glDisableClientState (GL_VERTEX_ARRAY);

	}
}