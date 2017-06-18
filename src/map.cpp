#include <GL/gl.h>
#include <GL/glu.h>

extern const GLint SCREEN_WIDTH;
extern const GLint SCREEN_HEIGHT;

namespace map {
	void Draw () {
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();
		glTranslatef (SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);
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