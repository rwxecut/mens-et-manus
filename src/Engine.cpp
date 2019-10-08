#include "Engine.h"
#include "Logger.h"
#include "auxiliary/errors.h"

#include <SDL_image.h>
#include "lua_binders/game_lua.h"
#include "lua_binders/nk_lua.h"


#define ENABLE_SPLASH true
#define AVERAGE_FPS_KEY SDL_SCANCODE_F2
#define WIREFRAME_MODE_KEY SDL_SCANCODE_F3


Engine::Engine () {
	// Create GL context
	if (!SDL_GL_CreateContext (window.get ()))
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

	// Create routines
	splash = new Splash (&routineHandler);
	mainMenu = new MainMenu ();
	game = new Game ();

	// Init routineHandler
	rTable = {nullptr, game, mainMenu, splash};
	routineHandler.assignRoutinesTable (rTable);
	routineHandler.id = ENABLE_SPLASH ? splashRoutine : mainMenuRoutine;

	nuklear = std::make_unique<_Nuklear> (window);
	lua = std::make_unique<_Lua> (window, nuklear, routineHandler);
}


Engine::~Engine () {
	for (Routine *routine: rTable)
		delete routine;
}


int Engine::mainLoop () {
	SDL_Event event;
	bool running = true;
	while (running) {
		running = routineHandler.switchID ();

		// Get events & update
		nk_input_begin (nuklear->ctx);
		while (SDL_PollEvent (&event))
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode) {
						case AVERAGE_FPS_KEY:
							window.switchFPSMeasure ();
							break;
						case WIREFRAME_MODE_KEY:
							window.switchWireframeMode ();
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
		nk_input_end (nuklear->ctx);
		routineHandler.update ();

		// Render
		routineHandler.render ();
		nk_sdl_render (NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
		glEnable (GL_DEPTH_TEST);
		window.render ();
	}
}


Engine::_SDL::_SDL () {
	// Init SDL
	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		fatalError ("SDL could not initialize!");
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
	logger.write ("SDL initialized");

	// Init SDL_image
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init (imgFlags) & imgFlags))
		fatalError ("SDL_image could not initialize!");
	logger.write ("SDL_image initialized");
}


Engine::_SDL::~_SDL () {
	IMG_Quit ();
	SDL_Quit ();
}


Engine::_Nuklear::_Nuklear (Window &window) {
	ctx = nk_sdl_init (window.get ());
	nk_font_atlas *atlas;
	nk_sdl_font_stash_begin (&atlas);
	nk_sdl_font_stash_end ();
	logger.write ("Nuklear initialized");
}


Engine::_Nuklear::~_Nuklear () {
	nk_sdl_shutdown ();
}


Engine::_Lua::_Lua (Window &window, Nuklear &nuklear, RoutineHandler &rHandler) {
	lua::game::init (window.get (), &rHandler);
	lua::nk::init (nuklear->ctx);
}