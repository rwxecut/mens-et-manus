#include <Config.h>
#include "Cam.h"


Cam::Cam () {
	moveSpeedMax = config.cam.moveSpeedMax;
	moveAcceleration = config.cam.moveAcceleration;
	zoomSpeed = config.cam.zoomSpeed;
}


void Cam::setup () {
	// Setup camera for drawing
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (FOV, config.screen.aspect, 1, renderDistance);
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
	pos += moveSpeed;
	sight += moveSpeed;
}


void Cam::zoom (int delta) {
	if ((delta > 0 && pos.z < maxZ) || (delta < 0 && pos.z > minZ))
		pos.z += delta * zoomSpeed;
}
