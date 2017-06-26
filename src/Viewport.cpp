#include <cstdio>
#include "Viewport.h"
#include "exceptions.h"

Viewport::Viewport (GameConfig const *config)
		: gConf (config)
	  , cam (config) {
	SDL_Log ("Debug SDL");

	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		throw video::SDL_Error (SDL_LOG_CATEGORY_APPLICATION,
				"SDL could not initialize!");

	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow ("Mens Et Manus",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			gConf->screen.width, gConf->screen.height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!window) throw video::SDL_Error (SDL_LOG_CATEGORY_VIDEO,
				"Window could not be created!");

	// Init OpenGL
	context = SDL_GL_CreateContext (window);
	if (!context) throw video::GL_Error ("Failed to create OpenGL context!");
	if (SDL_GL_SetSwapInterval (1) < 0)
		SDL_LogWarn (SDL_LOG_CATEGORY_VIDEO, "Can't enable VSync!");

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glClearColor (0.f, 0.f, 0.f, 1.f);
	if (glGetError () != GL_NO_ERROR)
		throw video::GL_Error ("Failed to initialize OpenGL!");
}


Viewport::~Viewport ()
{
	if (window) SDL_DestroyWindow (window);
	SDL_Quit ();
}


void Viewport::update () {
	keyHandler ();
	if (cam.moveSpeedX != 0 || cam.moveSpeedY != 0)
		cam.decelerate ();
	cam.move ();
}

void Viewport::render () {
	cam.setup ();
	map.draw ();
}

void Viewport::mousePositionHandler () {
	int mouseZoneMoveMap = 40; // TODO: move to config
	SDL_GetMouseState (&mouse.x, &mouse.y);
	// @formatter:off
	cam.accelerate ((mouse.x < mouseZoneMoveMap),
					(mouse.x > gConf->screen.width - mouseZoneMoveMap),
					(mouse.y < mouseZoneMoveMap),
					(mouse.y > gConf->screen.height - mouseZoneMoveMap));
	// @formatter:on
}

void Viewport::mouseScrollHandler (int32_t delta) {
	GLdouble scrollSpeed = 20.0;      //
	GLdouble minZ = 200.0;            // TODO: move to config
	GLdouble maxZ = 700.0;            //
	if ((delta > 0 && cam.pos.Z < maxZ) || (delta < 0 && cam.pos.Z > minZ))
		cam.pos.Z += delta * scrollSpeed;
}

void Viewport::keyHandler () {
	const uint8_t *keystates = SDL_GetKeyboardState (NULL);
	cam.accelerate (keystates[SDL_SCANCODE_LEFT], keystates[SDL_SCANCODE_RIGHT],
			keystates[SDL_SCANCODE_UP], keystates[SDL_SCANCODE_DOWN]);
}


void Viewport::mouseEventHandler (SDL_Event *event) {
	switch (event->type)
	{
		case SDL_MOUSEMOTION:
			char posstr[32];
			sprintf (posstr, "X: %d Y: %d", event->motion.x, event->motion.y);
			SDL_SetWindowTitle (window, posstr);
			break;
		case SDL_MOUSEWHEEL:
			mouseScrollHandler (event->wheel.y);
			break;
	}
}

void Viewport::mouseCommonHander ()
{
	mousePositionHandler ();
}

int Viewport::mainLoop () {
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
		SDL_GL_SwapWindow (window);
		mouseCommonHander ();
	}
	SDL_StopTextInput ();
	return 1;
}