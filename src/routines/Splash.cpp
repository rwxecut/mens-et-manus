#include "routines/Splash.h"
#include "Config.h"


Splash::Splash (RoutineHandler *rHandler) {
	this->rHandler = rHandler;

	// Load splash texture
	splashTex = new Texture (config.path.splash.c_str ());

	// Create shader program
	const char *vertShaderPath = config.path.splashVertShader.c_str ();
	const char *fragShaderPath = config.path.splashFragShader.c_str ();
	shaderProg = new ShaderProgram ("Splash", Shader::fromFile, vertShaderPath, Shader::fromFile, fragShaderPath);

	// Bind texture unit
	shaderProg->use ();
	shaderProg->setUniform ("splashTex", 0);

	GLfloat y = (GLfloat) (config.screen.aspect / splashTex->aspect ());
	//@formatter:off
	GLfloat vertices[] = {
	//		 x   y  s  t
			-1,  y, 0, 1,
			-1, -y, 0, 0,
			 1, -y, 1, 0,
			 1,  y, 1, 1
	};
	//@formatter:on
	splashRect = new gl::Rect (GL_STATIC_DRAW, vertices, sizeof (vertices));
	splashRect->setAttributes (0, 2, 4, 0); // X, Y
	splashRect->setAttributes (1, 2, 4, 2); // S, T
}


Splash::~Splash () {
	delete splashTex;
	delete shaderProg;
	delete splashRect;
}


void Splash::update () {
	alpha += d_alpha;
	if (alpha >= 0.8)
		d_alpha = -d_alpha;
	if (alpha <= 0)
		rHandler->id = mainMenuRoutine;
}


void Splash::render () {
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	splashTex->bind (0);
	shaderProg->use ();
	shaderProg->setUniform ("alpha", alpha);
	splashRect->draw ();
}


void Splash::eventHandler (SDL_Event *event) {}
