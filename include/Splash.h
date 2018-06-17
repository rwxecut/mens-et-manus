#pragma once


#include "Routine.h"
#include "Config.h"
#include "Texture.h"


class Splash : public Routine {

	Texture *splash;
	RoutineHandler *rHandler;

public:

	Splash (RoutineHandler *rHandler);
	~Splash ();

	void update ();
	void render ();
	void eventHandler (SDL_Event *event);
};
