#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include <stdio.h>

#include "GameConfig.h"
#include "main_menu.h"
#include "map.h"

GameConfig const *GCONF = NULL;

void render ();
bool initSDL ();
bool initGL ();
void final ();

inline bool SDL_error (const char *msg);
inline void SDL_warning (const char *msg);
inline bool GL_error (const char *msg);

SDL_Window *Window = NULL;
SDL_GLContext Context;

int main (int argc, char *args[]) {

	GCONF = new GameConfig ("config.lua");
	if (!GCONF->valid ())
		final ();

	if (!initSDL () | !initGL ())
		final ();

	SDL_error ("Debug SDL");
	GL_error ("Debug GL");

	SDL_StartTextInput ();
	bool running = true;
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent (&event)) {
			if (event.type == SDL_QUIT)
				running = false;
		}
		render ();
		SDL_GL_SwapWindow (Window);
	}
	SDL_StopTextInput ();

	final ();
	return 0;
}

void render () {
	map::Draw ();
}

bool initSDL () {
	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		return SDL_error ("SDL could not initialize!");
	Window = SDL_CreateWindow ("Mens Et Manus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GCONF->screen.width,
			GCONF->screen.height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!Window)
		return SDL_error ("Window could not be created!");
	return true;
}

bool initGL () {
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 1);
	Context = SDL_GL_CreateContext (Window);
	if (!Context)
		return SDL_error ("Failed to create OpenGL \n context!");
	if (SDL_GL_SetSwapInterval (1) < 0)
		SDL_warning ("Can't enable VSync!");

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0.0, GCONF->screen.width, GCONF->screen.height, 0.0, 1.0, -1.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glClearColor (0.f, 0.f, 0.f, 1.f);
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
