#include "Engine.h"
#include "Logger.h"
#include "Config.h"
#include "auxiliary/errors.h"

#include <SDL_image.h>
#include <SDL_net.h>
#include "lua_binders/game_lua.h"
#include "lua_binders/nk_lua.h"


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

	routineHandler.new_id = splashRoutine;

	nuklear = std::make_unique<_Nuklear> (window);
	lua = std::make_unique<_Lua> (window, nuklear, routineHandler);
}


Engine::~Engine () {}


int Engine::mainLoop () {
	SDL_Event event;
	bool running = routineHandler.switchID ();
	while (running) {
		// Get events & update
		nk_input_begin (nuklear->ctx);
		while (SDL_PollEvent (&event))
			switch (event.type) {
				[[unlikely]]
				case SDL_QUIT:
					routineHandler.new_id = finalization;
					break;
				case SDL_KEYDOWN:
					handleKeydown (event.key.keysym.scancode);
					[[fallthrough]];
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

		// Finish Splash
		[[unlikely]]
		if (routineHandler.id == splashRoutine && routineHandler.finished())
				routineHandler.new_id = mainMenuRoutine;
		running = routineHandler.switchID ();
	}
	return 0;
}


void Engine::handleKeydown (SDL_Scancode scancode) {
	switch (scancode) {
		case AVERAGE_FPS_KEY:
			window.switchFPSMeasure ();
			break;
		case WIREFRAME_MODE_KEY:
			window.switchWireframeMode ();
			break;
		default:
			break;
	}
}


Engine::_SDL::_SDL () {
	// Init SDL
	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		fatalError ("SDL init error: %s", SDL_GetError());
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
	logger.write ("SDL initialized");

	// Init SDL_image
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init (imgFlags) & imgFlags))
		fatalError ("SDL_image init error: %s", IMG_GetError());
	logger.write ("SDL_image initialized");

	// Init SDL_net
	if (SDLNet_Init() == -1)
		fatalError("SDL_net init error: %s", SDLNet_GetError());
	logger.write ("SDL_image initialized");
}


Engine::_SDL::~_SDL () {
	SDLNet_Quit();
	IMG_Quit ();
	SDL_Quit ();
}


Engine::_Nuklear::_Nuklear (Window &window) {
	ctx = nk_sdl_init (window.get ());
	nk_font_atlas *atlas;
	nk_sdl_font_stash_begin (&atlas);
	nk_font *font = nk_font_atlas_add_from_file (atlas, config.path.font.c_str(), config.fontSize, 0);
	nk_sdl_font_stash_end ();
	nk_style_set_font (ctx, &font->handle);
	logger.write ("Nuklear initialized");
}


Engine::_Nuklear::~_Nuklear () {
	nk_sdl_shutdown ();
}


Engine::_Lua::_Lua (Window &window, Nuklear &nuklear, RoutineHandler &rHandler) {
	// Give Lua binders access to static game handlers
	lua::bind::Game::init (window.get (), &rHandler);
	lua::bind::Nuklear::init (nuklear->ctx);
}
