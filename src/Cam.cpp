#include <Config.h>
#include "Cam.h"

Cam::Cam (Config *config) {
	moveSpeedMax = config -> cam.moveSpeedMax;
	moveAcceleration = config -> cam.moveAcceleration;
	zoomSpeed = config -> cam.zoomSpeed;
}

const GLdouble Cam::FOV = 90.0;
const GLdouble Cam::renderDistance = 1000.0;
const GLdouble Cam::minZ = 200.0;
const GLdouble Cam::maxZ = 700.0;

void Cam::setup () {
	// Setup camera for drawing
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (FOV, 1, 1, renderDistance);
	gluLookAt (pos.x, pos.y, pos.z, sight.x, sight.y, sight.z, 0, 1, 0);
}

void Cam::accelerate (direction_t *dir) {
	// Accelerate camera if moving
	if (dir->left && (moveSpeed.x >= -moveSpeedMax))
		moveSpeed.x -= 2 * moveAcceleration;
	if (dir->right && (moveSpeed.x <= moveSpeedMax))
		moveSpeed.x += 2 * moveAcceleration;
	if (dir->up && (moveSpeed.y <= moveSpeedMax))
		moveSpeed.y += 2 * moveAcceleration;
	if (dir->down && (moveSpeed.y >= -moveSpeedMax))
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
	pos.y += moveSpeed.y;
	sight.x += moveSpeed.x;
	sight.y += moveSpeed.y;
}

void Cam::zoom (int delta) {
	if ((delta > 0 && pos.z < maxZ) || (delta < 0 && pos.z > minZ))
		pos.z += delta * zoomSpeed;
}
