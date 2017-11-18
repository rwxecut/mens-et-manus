#include "Window.h"


Window::Window (Config *config)
		: game (config) {
	winState.attrib.screenSize.width = config->screen.width;
	winState.attrib.screenSize.height = config->screen.height;

	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		throw video::SDL_Error (SDL_LOG_CATEGORY_APPLICATION,
		                        "SDL could not initialize!");

	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

	sdlWindow = SDL_CreateWindow ("Mens Et Manus",
	                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	                              winState.attrib.screenSize.width, winState.attrib.screenSize.height,
	                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!sdlWindow)
		throw video::SDL_Error (SDL_LOG_CATEGORY_VIDEO,
		                        "Window could not be created!");

	// Init OpenGL
	glContext = SDL_GL_CreateContext (sdlWindow);
	if (!glContext)
		throw video::GL_Error ("Failed to create OpenGL context!");
	if (SDL_GL_SetSwapInterval (1) < 0)
		SDL_LogWarn (SDL_LOG_CATEGORY_VIDEO, "Can't enable VSync!");

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glClearColor (0.f, 0.f, 0.f, 1.f);
	glEnable (GL_DEPTH_TEST);
	if (glGetError () != GL_NO_ERROR)
		throw video::GL_Error ("Failed to initialize OpenGL!");

	nkContext = nk_sdl_init (sdlWindow);
	winState.nkContext = nkContext;
	struct nk_font_atlas *atlas;
	nk_sdl_font_stash_begin (&atlas);
	nk_sdl_font_stash_end ();
	game.loadLuaNk (&winState);

	routine = &game;
}


Window::~Window () {
	nk_sdl_shutdown ();
	if (sdlWindow) SDL_DestroyWindow (sdlWindow);
	SDL_Quit ();
}


int Window::mainLoop () {
	SDL_Event event;
	bool running = true;
	while (running) {
		nk_input_begin (nkContext);
		while (SDL_PollEvent (&event))
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				default:
					nk_sdl_handle_event (&event);
					routine->eventHandler (&event);
			}
		nk_input_end (nkContext);
		routine->update (&winState);
		routine->render ();
		nk_sdl_render (NK_ANTI_ALIASING_ON);
		glFlush ();
		SDL_GL_SwapWindow (sdlWindow);
		SDL_GetMouseState (&winState.mousePos.x, &winState.mousePos.y);
	}
	return 0;
}
