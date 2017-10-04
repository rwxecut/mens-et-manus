#pragma once

#include <GL/glu.h>
#include <Config.h>
#include "geometry.h"

typedef struct {
	bool left, right, up, down;
} direction_t;

class Cam {
	friend class Game;

	// General variables & methods
	static const GLdouble FOV, renderDistance;
	point3d<GLdouble> pos = {0, -100, 500}, sight = {0, 0, 0};
	void setup ();

	// Moving variables & methods
	vector2d<GLdouble> moveSpeed;
	GLdouble moveSpeedMax, moveAcceleration;
	GLdouble zoomSpeed;
	static const GLdouble minZ, maxZ;
	void accelerate (direction_t *dir);
	void decelerate ();
	void move ();
	void zoom (int delta);

public:
	Cam (Config *config);
};
