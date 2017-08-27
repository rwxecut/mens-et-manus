#pragma once

#include <GL/glu.h>
#include <Config.h>
#include "geometry.h"

class Cam {

public:
	Cam (Config *config);

	// General variables & methods
	GLdouble FOV;
	static const GLdouble renderDistance;
	point3d<GLdouble> pos = {0, -100, 500}, sight = {0, 0, 0};
	void setup ();

	// Moving variables & methods
	vector2d<GLdouble> moveSpeed;
	static const GLdouble moveSpeedMax;
	GLdouble moveAcceleration = 0.5;    // TODO: move to config
	void accelerate (bool left, bool right, bool up, bool down);
	void decelerate ();
	void move ();
};