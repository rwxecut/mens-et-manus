#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include <cstdio>

#include "mouse.h"
#include "GameConfig.h"
#include "main_menu.h"
#include "map.h"

GameConfig const *GCONF = NULL;

void update ();
void render ();
bool init ();
void final ();

inline bool SDL_error (const char *msg);
inline void SDL_warning (const char *msg);
inline bool GL_error (const char *msg);

SDL_Window *Window = NULL;
SDL_GLContext Context;

int main (int argc, char *args[]) {
	if (!init ()) exit (7);

	SDL_error ("Debug SDL");
	GL_error ("Debug GL");

	map::Init ();

	// Main loop
	bool running = true;
	SDL_StartTextInput ();
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent (&event))
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_MOUSEMOTION:
				case SDL_MOUSEWHEEL:
					mouseEventHandler (&event);
					break;
			}
		update ();
		render ();
		glFlush ();
		SDL_GL_SwapWindow (Window);

		mouseCommonHander ();
	}
	SDL_StopTextInput ();

	final ();
	return 0;
}

void update () {
	map::Update ();
}

void render () {
	// Here will be all rendering routines
	map::Draw ();
}

bool init () {
	// Load config
	GCONF = new GameConfig ();
	if (!GCONF->valid ()) exit (7); //temporary

	// Init SDL
	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		return SDL_error ("SDL could not initialize!");
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
	Window = SDL_CreateWindow ("Mens Et Manus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GCONF->screen.width,
							   GCONF->screen.height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!Window) return SDL_error ("Window could not be created!");

	// Init OpenGL
	Context = SDL_GL_CreateContext (Window);
	if (!Context) return SDL_error ("Failed to create OpenGL context!");
	if (SDL_GL_SetSwapInterval (1) < 0)
		SDL_warning ("Can't enable VSync!");

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glClearColor (0.f, 0.f, 0.f, 1.f);
	if (glGetError () != GL_NO_ERROR) return GL_error ("Failed to initialize OpenGL!");
	return true;
}

void final () {
	if (Window) SDL_DestroyWindow (Window);
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
