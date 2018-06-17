#include "Window.h"

#define ENABLE_SPLASH true


Window::Window () {
	// Load attributes from config
	fpsMeasureInterval = config.fpsMeasureInterval * 1000;
	bool fullscreen = config.screen.fullscreen;

	// Init SDL
	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		fatalError ("SDL could not initialize!");

	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

	sdlWindow = SDL_CreateWindow ("Mens et Manus",
	                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                              config.screen.size.width, config.screen.size.height,
	                              SDL_WINDOW_OPENGL | (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
	if (!sdlWindow)
		fatalError ("Window could not be created!");
	logger.write ("SDL initialized");

	// Init SDL_image
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init (imgFlags) & imgFlags))
		fatalError ("SDL_image could not initialize!");
	logger.write ("SDL_image initialized");

	// Create GL context
	glContext = SDL_GL_CreateContext (sdlWindow);
	if (!glContext)
		fatalError ("Failed to create OpenGL context!");
	logger.write ("SDL GL context created");
	if (SDL_GL_SetSwapInterval (1) < 0)
		logger.write ("WARNING: Can't enable VSync");
	logger.write ("VSync enabled");

	// Init OpenGL
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glClearColor (0, 0, 0, 1);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_TEXTURE_2D);
	if (glGetError () != GL_NO_ERROR)
		fatalError ("Failed to initialize OpenGL!");
	logger.write ("OpenGL initialized");

	// Init Nuklear
	nkContext = nk_sdl_init (sdlWindow);
	nk_font_atlas *atlas;
	nk_sdl_font_stash_begin (&atlas);
	nk_sdl_font_stash_end ();
	logger.write ("Nuklear initialized");

	// Create routines
	splash = new Splash (&routineHandler);
	mainMenu = new MainMenu ();
	game = new Game ();

	// Init routineHandler
	rTable = {nullptr, game, mainMenu, splash};
	routineHandler.assignRoutinesTable (rTable);
	routineHandler.id = ENABLE_SPLASH ? splashRoutine : mainMenuRoutine;

	// Init lua binders
	lua::game::init (sdlWindow, &routineHandler);
	lua::nk::init (nkContext);
}


Window::~Window () {
	for (Routine *routine: rTable)
		delete routine;
	nk_sdl_shutdown ();
	if (sdlWindow) SDL_DestroyWindow (sdlWindow);
	IMG_Quit ();
	SDL_Quit ();
}


uint32_t Window::getFPS () {
	static uint32_t FPS = 0;
	static uint32_t frames = 0;
	static uint32_t lasttime = SDL_GetTicks ();

	frames++;
	if (lasttime < SDL_GetTicks () - fpsMeasureInterval) {
		lasttime = SDL_GetTicks ();
		FPS = frames;
		frames = 0;
	}
	return FPS;
}


int Window::mainLoop () {
	SDL_Event event;
	bool running = true;
	while (running) {
		running = routineHandler.switchID ();

		// Get events & update
		nk_input_begin (nkContext);
		while (SDL_PollEvent (&event))
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				default:
					nk_sdl_handle_event (&event);
					routineHandler.eventHandler (&event);
			}
		nk_input_end (nkContext);
		routineHandler.update ();

		// Render
		routineHandler.render ();
		nk_sdl_render (NK_ANTI_ALIASING_ON);
		glFlush ();
		SDL_GL_SwapWindow (sdlWindow);

		// Write FPS to window title
		char fpsStr[32] = {0};
		snprintf (fpsStr, sizeof (fpsStr), "Mens et Manus [FPS: %zu]", getFPS ());
		SDL_SetWindowTitle (sdlWindow, fpsStr);
	}
	return 0;
}
