#include "Splash.h"


Splash::Splash (RoutineHandler *rHandler) {
	splash = new Texture (config.path.splash.c_str ());
	this->rHandler = rHandler;
}


Splash::~Splash () {
	delete splash;
}


void Splash::update () {
	// dumb temporarily workaround
	static int cntr = 0;
	cntr++;
	SDL_Delay (10);
	if (cntr == 100)
		rHandler->id = mainMenuRoutine;
}


void Splash::render () {
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	GLfloat y = (GLfloat) (config.screen.aspect / splash->aspect ());
	//@formatter:off
	GLfloat vertex[] = {-1,  y, 0,
	                    -1, -y, 0,
	                     1, -y, 0,
	                     1,  y, 0};
	GLfloat texCoords[] = {0, 0,
	                       0, 1,
	                       1, 1,
	                       1, 0};
	//@formatter:on
	splash->stateDraw (GL_QUADS, 4, vertex, texCoords);
}


void Splash::eventHandler (SDL_Event *event) {}
