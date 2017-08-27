#include <Config.h>
#include "Cam.h"

Cam::Cam (Config *config) {
	FOV = config->cam.FOV;
}

const GLdouble Cam::renderDistance = 1000.0f;
const GLdouble Cam::moveSpeedMax = 10.0f;

void Cam::setup () {
	// Setup camera for drawing
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (FOV, 1, 1, renderDistance);
	gluLookAt (pos.x, pos.y, pos.z, sight.x, sight.y, sight.z, 0, 1, 0);
}

void Cam::accelerate (bool left, bool right, bool up, bool down) {
	// Accelerate camera if moving
	if (left && (moveSpeed.x >= -moveSpeedMax))
		moveSpeed.x -= 2 * moveAcceleration;
	if (right && (moveSpeed.x <= moveSpeedMax))
		moveSpeed.x += 2 * moveAcceleration;
	if (up && (moveSpeed.y <= moveSpeedMax))
		moveSpeed.y += 2 * moveAcceleration;
	if (down && (moveSpeed.y >= -moveSpeedMax))
		moveSpeed.y -= 2 * moveAcceleration;
}

void Cam::decelerate () {
	// Decelerate camera if stopping moving
	if (moveSpeed.x < 0) moveSpeed.x += moveAcceleration;
	if (moveSpeed.x > 0) moveSpeed.x -= moveAcceleration;
	if (moveSpeed.y < 0) moveSpeed.y += moveAcceleration;
	if (moveSpeed.y > 0) moveSpeed.y -= moveAcceleration;
}

void Cam::move () {
	pos.x += moveSpeed.x;
	sight.x += moveSpeed.x;
	pos.y += moveSpeed.y;
	sight.y += moveSpeed.y;
}