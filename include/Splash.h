#pragma once

#include "Routine.h"
#include "Texture.h"

class Splash : public Routine {

	Texture *splash;
	RoutineHandler *rHandler;
	GLfloat alpha = 0, d_alpha = 0.01;


public:

	Splash (RoutineHandler *rHandler);
	~Splash ();

	void update ();
	void render ();
	void eventHandler (SDL_Event *event);
};
