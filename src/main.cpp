#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include <stdio.h>

#include "main_menu.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *Window = NULL;
SDL_Surface *Surface = NULL;
SDL_GLContext Context;

bool initSDL ();
bool initGL ();
void final ();

inline bool SDL_error (const char *msg);
inline void SDL_warning (const char *msg);
inline bool GL_error (const char *msg);

int main (int argc, char *args[]) {
	if (!initSDL () | !initGL())
		final ();

	mainMenu::Draw ();
	SDL_error ("Debug SDL");
	GL_error ("Debug GL");
	SDL_Delay (3000);

	final ();
	return 0;
}

bool initSDL () {
	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		return SDL_error ("SDL could not initialize!");
	Window = SDL_CreateWindow ("Mens Et Manus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
							   SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!Window)
		return SDL_error ("Window could not be created!");
	Surface = SDL_GetWindowSurface (Window);
	return true;
}

bool initGL () {
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 0);
	Context = SDL_GL_CreateContext (Window);
	if (!Context)
		return SDL_error ("Failed to create OpenGL context!");
	if (SDL_GL_SetSwapInterval (1) < 0)
		SDL_warning ("Can't enable VSync!");

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	if (glGetError () != GL_NO_ERROR)
		return GL_error ("Failed to initialize OpenGL!");
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	if (glGetError () != GL_NO_ERROR)
		return GL_error ("Failed to initialize OpenGL!");
	return true;
}

void final () {
	if (Window)
		SDL_DestroyWindow (Window);
	SDL_Quit ();
}

inline bool SDL_error (const char *msg) {
	fprintf (stderr, "ERROR: %s SDL_Error: %s\n", msg, SDL_GetError ());
	return false;
}

inline void SDL_warning (const char *msg) {
	fprintf (stderr, "WARNING: %s SDL_Error: %s\n", msg, SDL_GetError ());
}

inline bool GL_error (const char *msg) {
	fprintf (stderr, "ERROR: %s GL_Error: %s\n", msg, gluErrorString (glGetError ()));
	return false;
}
