#pragma once

#include "Routine.h"
#include "Shader.h"
#include "Texture.h"
#include "auxiliary/primitives.h"

#include <memory>

class Splash : public Routine {

	TexturePtr splashTex;
	RoutineHandler *rHandler;
	GLfloat alpha = 0, d_alpha = 0.01;

	gl::RectPtr splashRect;
	ShaderProgramPtr shaderProg;


public:
	Splash (RoutineHandler *rHandler);

	void update ();
	void render ();
	void eventHandler (SDL_Event *event);
};
