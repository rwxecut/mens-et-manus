#include "Window.h"
#include <cstdio>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "lua_binders/game_lua.h"
#include "lua_binders/nk_lua.h"
#include "auxiliary/geometry.h"
#include "auxiliary/errors.h"
#include "Logger.h"
#include "Config.h"


#define ENABLE_SPLASH true
#define AVERAGE_FPS_KEY SDL_SCANCODE_F2
#define WIREFRAME_MODE_KEY SDL_SCANCODE_F3


Window::Window () {
	// Load attributes from config
	fpsMeasureInterval = config.fpsMeasureInterval * 1000;
	bool fullscreen = config.screen.fullscreen;

	// Init SDL
	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		fatalError ("SDL could not initialize!");

	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
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
		warnError ("Can't enable VSync");
	logger.write ("VSync enabled");

	// Load OpenGL
	if (!gladLoadGLLoader (SDL_GL_GetProcAddress))
		fatalError ("Failed to load OpenGL!");

	// Init OpenGL
	glClearColor (0, 0, 0, 1);
	glEnable (GL_DEPTH_TEST);
	if (glGetError () != GL_NO_ERROR)
		fatalError ("Failed to initialize OpenGL!");
	logger.write_inc ("OpenGL initialized");
	logger.write_dec ("Render device: %s", glGetString (GL_RENDERER));

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


int Window::mainLoop () {
	SDL_Event event;
	bool running = true;
	while (running) {
		running = routineHandler.switchID ();

		// Get events & update
		nk_input_begin (nkContext);
		while (SDL_PollEvent (&event))
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode) {
						case AVERAGE_FPS_KEY:
							averageEnabled = !averageEnabled;
							averageSwitched = true;
							break;
						case WIREFRAME_MODE_KEY:
							switchWireframeMode ();
							break;
						default:
							break;
					}
					break;
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
		nk_sdl_render (NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
		glEnable (GL_DEPTH_TEST);
		SDL_GL_SwapWindow (sdlWindow);

		// Write FPS to window title or log
		writeFPS ();
	}
	return 0;
}


size_t Window::getFPS (float *average) {
	static size_t FPS = 0;
	static size_t frames = 0;
	static uint32_t lasttime = SDL_GetTicks ();

	static uint64_t ticks = 0;
	static float averageFPS = 0;

	frames++;
	if (lasttime < SDL_GetTicks () - fpsMeasureInterval) {
		lasttime = SDL_GetTicks ();
		FPS = frames;
		frames = 0;

		if (average) {
			averageFPS = averageFPS * (ticks / (ticks + 1.0f)) + FPS / (ticks + 1.0f);
			ticks++;
		}
	}

	if (average)
		*average = averageFPS;
	return FPS;
}


void Window::writeFPS () {
	size_t FPS = 0;
	static float avFPS = 0;
	char fpsStr[64] = {0};

	if (averageEnabled) {
		if (averageSwitched)
			logger.write ("Started measuring average FPS");
		FPS = getFPS (&avFPS);
		snprintf (fpsStr, sizeof (fpsStr), "Mens et Manus [FPS: %zu] [Average: %g]", FPS, avFPS);
	} else {
		if (averageSwitched) {
			logger.write ("Stopped measuring average FPS: %g", avFPS);
			avFPS = 0;
		}
		FPS = getFPS (NULL);
		snprintf (fpsStr, sizeof (fpsStr), "Mens et Manus [FPS: %zu]", FPS);
	}
	averageSwitched = false;

	SDL_SetWindowTitle (sdlWindow, fpsStr);
}


void Window::switchWireframeMode () {
	static bool wireframeEnabled = false;

	wireframeEnabled = !wireframeEnabled;
	glPolygonMode (GL_FRONT_AND_BACK, wireframeEnabled ? GL_LINE : GL_FILL);
}
