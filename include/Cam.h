#pragma once

#include "lib/glad.h"
#include "auxiliary/geometry.h"

#include "lib/glm/vec2.hpp"
#include "lib/glm/vec3.hpp"
#include "lib/glm/mat4x4.hpp"

typedef struct {
	bool left, right, up, down;
} direction_t;

class Cam {
	friend class Game;

	// General variables & methods
	static constexpr GLdouble FOV = 90.0;
	static constexpr GLdouble renderDistance = 1100.0;
	glm::vec3 pos = {0, -100, 500}, sight = {0, 0, 0};
	void setup (glm::mat4 *MVP);

	glm::mat4 projection, modelview;

	// Moving variables & methods
	glm::vec3 moveSpeed = {0, 0, 0};
	GLdouble moveSpeedMax, moveAcceleration;
	GLdouble zoomSpeed;
	static constexpr GLdouble minZ = 200;
	static constexpr GLdouble maxZ = 800;
	void accelerate (direction_t *dir);
	void decelerate ();
	void move ();
	void zoom (int delta);

public:
	glm::ivec2 unproject (const glm::vec2 &source);

	Cam ();
};
