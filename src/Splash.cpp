#include "Splash.h"
#include "Config.h"


Splash::Splash (RoutineHandler *rHandler) {
	splash = new Texture (config.path.splash.c_str ());
	this->rHandler = rHandler;
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


Splash::~Splash () {
	delete splash;
}


void Splash::update () {
	alpha += d_alpha;
	if (alpha >= 1)
		d_alpha = -d_alpha;
	if (alpha <= 0) {
		glDisable (GL_BLEND);
		rHandler->id = mainMenuRoutine;
	}
}


void Splash::render () {
	if (alpha <= 0) return;
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
	glColor4f (1, 1, 1, alpha);
	splash->stateDraw (GL_QUADS, 4, vertex, texCoords);
}


void Splash::eventHandler (SDL_Event *event) {}
