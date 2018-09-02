#pragma once

#include "Routine.h"
#include "Shader.h"
#include "Texture.h"
#include "auxiliary/primitives.h"

class Splash : public Routine {

	Texture *splashTex;
	RoutineHandler *rHandler;
	GLfloat alpha = 0, d_alpha = 0.01;

	gl::Rect *splashRect;
	ShaderProgram *shaderProg;


public:

	Splash (RoutineHandler *rHandler);
	~Splash ();

	void update ();
	void render ();
	void eventHandler (SDL_Event *event);
};
