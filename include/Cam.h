#pragma once

#include <GL/glu.h>
#include "GameConfig.h"

class Cam {

public:
	Cam (GameConfig const *gConf);

	// General variables & methods
	GLdouble FOV;
	GLdouble renderDistance;
	struct {
		GLdouble X, Y, Z;
	} pos;
	struct {
		GLdouble X = 0, Y = 0, Z = 0;
	} sight;
	void setup ();

	// Moving variables & methods
	GLdouble moveSpeedX, moveSpeedY;
	GLdouble moveAcceleration = 0.5;    // TODO: move to config
	void accelerate (bool left, bool right, bool up, bool down);
	void decelerate ();
	void move ();
};