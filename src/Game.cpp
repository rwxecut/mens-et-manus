#include <Game.h>

Game::Game (Config *config)
		: cam (config) {
	attrib.screenSize.width = config->screen.width;
	attrib.screenSize.height = config->screen.height;

	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		throw video::SDL_Error (SDL_LOG_CATEGORY_APPLICATION,
		                        "SDL could not initialize!");

	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow ("Mens Et Manus",
	                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	                           attrib.screenSize.width, attrib.screenSize.height,
	                           SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!window)
		throw video::SDL_Error (SDL_LOG_CATEGORY_VIDEO,
		                        "Window could not be created!");

	// Init OpenGL
	glContext = SDL_GL_CreateContext (window);
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


Game::~Game () {
	if (window) SDL_DestroyWindow (window);
	SDL_Quit ();
}


void Game::update () {
	keyHandler ();
	if (cam.moveSpeedX != 0 || cam.moveSpeedY != 0)
		cam.decelerate ();
	cam.move ();

	GLdouble unprojX, unprojY;
	unproject (mouse.x, mouse.y, &unprojX, &unprojY);
	map.getHoveredTile (unprojX, unprojY);

	// Print debug info to title
	char posstr[64];
	std::sprintf (posstr, "X: %d Y: %d posX: %0.1f posY: %0.1f",
	              mouse.x, mouse.y, unprojX, unprojY);
	SDL_SetWindowTitle (window, posstr);
}


void Game::render () {
	cam.setup ();
	map.draw ();
}


void Game::unproject (GLdouble srcX, GLdouble srcY,
                      GLdouble *objX, GLdouble *objY) {
	GLdouble modelview[16], projection[16];
	GLint viewport[4];
	GLfloat srcZ;
	GLdouble objZ;

	glGetDoublev (GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev (GL_PROJECTION_MATRIX, projection);
	glGetIntegerv (GL_VIEWPORT, viewport);
	srcY = (GLfloat) (viewport[3] - srcY);
	glReadPixels ((GLint) srcX, (GLint) srcY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &srcZ);
	gluUnProject (srcX, srcY, srcZ, modelview, projection, viewport, objX, objY, &objZ);
}


void Game::mousePositionHandler () {
	int mouseZoneMoveMap = 40; // TODO: move to config
	SDL_GetMouseState (&mouse.x, &mouse.y);
	// @formatter:off
	cam.accelerate ((mouse.x < mouseZoneMoveMap),
					(mouse.x > attrib.screenSize.width - mouseZoneMoveMap),
					(mouse.y < mouseZoneMoveMap),
					(mouse.y > attrib.screenSize.height - mouseZoneMoveMap));
	// @formatter:on
}


void Game::mouseScrollHandler (int32_t delta) {
	GLdouble scrollSpeed = 20.0;      //
	GLdouble minZ = 200.0;            // TODO: move to config
	GLdouble maxZ = 700.0;            //
	if ((delta > 0 && cam.pos.Z < maxZ) || (delta < 0 && cam.pos.Z > minZ))
		cam.pos.Z += delta * scrollSpeed;
}


void Game::keyHandler () {
	const uint8_t *keystates = SDL_GetKeyboardState (NULL);
	cam.accelerate (keystates[SDL_SCANCODE_LEFT], keystates[SDL_SCANCODE_RIGHT],
	                keystates[SDL_SCANCODE_UP], keystates[SDL_SCANCODE_DOWN]);
}


int Game::mainLoop () {
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
		SDL_GL_SwapWindow (window);
		mousePositionHandler ();
	}
	return 1;
}
