#pragma once

#include "Routine.h"
#include "Shader.h"
#include "Texture.h"
#include "auxiliary/primitives.h"

class Splash : public Routine {

	TexturePtr splashTex;
	GLfloat alpha = 0, d_alpha = 0.01;

	gl::RectPtr splashRect;
	ShaderProgramPtr shaderProg;


public:
	Splash ();

	void update ();
	void render ();
	void eventHandler (SDL_Event *event);

	bool finished = false;
};
