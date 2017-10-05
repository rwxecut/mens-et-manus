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
	static constexpr GLdouble FOV = 90.0;
	static constexpr GLdouble renderDistance = 1000.0;
	point3d<GLdouble> pos = {0, -100, 500}, sight = {0, 0, 0};
	void setup ();

	// Moving variables & methods
	vector2d<GLdouble> moveSpeed;
	GLdouble moveSpeedMax, moveAcceleration;
	GLdouble zoomSpeed;
	static constexpr GLdouble minZ = 200.0;
	static constexpr GLdouble maxZ = 700.0;
	void accelerate (direction_t *dir);
	void decelerate ();
	void move ();
	void zoom (int delta);

public:
	Cam (Config *config);
};
