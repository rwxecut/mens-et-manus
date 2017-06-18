#include <GL/gl.h>

namespace mainMenu {
	void Draw () {
		glClear (GL_COLOR_BUFFER_BIT);
		glBegin (GL_QUADS);
			glVertex2f (-0.5f, -0.5f);
			glVertex2f (0.5f, -0.5f);
			glVertex2f (0.5f, 0.5f);
			glVertex2f (-0.5f, 0.5f);
		glEnd ();
	}
}
