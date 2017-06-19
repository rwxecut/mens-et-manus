#include <GL/gl.h>
#include <GL/glu.h>

extern const GLint SCREEN_WIDTH, SCREEN_HEIGHT;

namespace map {
	void Draw () {
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();
		glTranslatef (SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 1.f);
		//gluPerspective (45.f, 1, 2.f, 50.f);
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		glOrtho (0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

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
		glDrawArrays (GL_LINE_LOOP, 0, 6);
		glDisableClientState (GL_VERTEX_ARRAY);
	}
}