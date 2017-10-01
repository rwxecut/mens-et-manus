#include "Window.h"

Window::Window (Config *config)
	: game (config) {
	attrib.screenSize.width = config->screen.width;
	attrib.screenSize.height = config->screen.height;

	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		throw video::SDL_Error (SDL_LOG_CATEGORY_APPLICATION,
		                        "SDL could not initialize!");

	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

	sdlWindow = SDL_CreateWindow ("Mens Et Manus",
	                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	                              attrib.screenSize.width, attrib.screenSize.height,
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
}


Window::~Window () {
	if (sdlWindow) SDL_DestroyWindow (sdlWindow);
	SDL_Quit ();
}


void Window::update () {
	keyHandler ();
	game.update (mouse.pos.x, mouse.pos.y);
}

void Window::render () {
	game.render ();
}


void Window::keyHandler () {
	const uint8_t *keystates = SDL_GetKeyboardState (NULL);
	game.keyHandler (keystates);
}

void Window::mousePositionHandler () {
	SDL_GetMouseState (&mouse.pos.x, &mouse.pos.y);
	game.mousePositionHandler (attrib.screenSize.width, attrib.screenSize.height, mouse.pos.x, mouse.pos.y);
}


void Window::mouseScrollHandler (int32_t delta) {
	game.mouseScrollHandler (delta);
}


int Window::mainLoop () {
	bool running = true;
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent (&event))
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_MOUSEWHEEL:
					mouseScrollHandler (event.wheel.y);
					break;
				default:
					break;
			}
		update ();
		render ();
		glFlush ();
		SDL_GL_SwapWindow (sdlWindow);
		mousePositionHandler ();
	}
	return 1;
}
