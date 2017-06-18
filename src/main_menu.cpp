#include <SDL.h>
#include <GL/gl.h>

extern SDL_Window *Window;
extern SDL_Surface *Surface;

namespace mainMenu {
	void Draw() {
		SDL_FillRect(Surface, NULL, SDL_MapRGB(Surface->format, 0xFF, 0xFF, 0xFF));

		glLineWidth(2.5);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(15, 0, 0);
		glEnd();

		SDL_UpdateWindowSurface(Window);
	}
}
