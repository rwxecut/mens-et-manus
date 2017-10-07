#include "Window.h"


Window::Window (Config *config)
		: menu (), game (config) {
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

	game.active = true;
}


Window::~Window () {
	if (sdlWindow) SDL_DestroyWindow (sdlWindow);
	SDL_Quit ();
}


void Window::update () {
	keyHandler ();
	if (game.active)
		game.update (mouse.pos);
	if (menu.active)
		menu.update (mouse.pos);
}


void Window::render () {
	if (game.active)
		game.render ();
	if (menu.active)
		menu.render ();
}


void Window::keyHandler () {
	const uint8_t *keystates = SDL_GetKeyboardState (NULL);
	if (keystates[SDL_SCANCODE_Q]) {
		game.active ^= true;
		menu.active ^= true;
	}
	if (game.active)
		game.keyHandler (keystates);
	if (menu.active)
		menu.keyHandler (keystates);
}


void Window::Mouse::positionHandler (Window *window) {
	SDL_GetMouseState (&pos.x, &pos.y);
	window->game.mousePositionHandler (window->attrib.screenSize, pos);
}


void Window::Mouse::scrollHandler (Window *window, int32_t delta) {
	window->game.mouseScrollHandler (delta);
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
					mouse.scrollHandler (this, event.wheel.y);
					break;
				default:
					break;
			}
		update ();
		render ();
		glFlush ();
		SDL_GL_SwapWindow (sdlWindow);
		mouse.positionHandler (this);
	}
	return 1;
}
