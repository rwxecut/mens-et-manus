#include "Cam.h"

Cam::Cam (GameConfig const *gConf) {
	// Init camera values from config
	FOV = gConf->video.cam.fov;
	renderDistance = gConf->video.cam.renderDistance;
	pos.X = gConf->video.cam.pos.x;
	pos.Y = gConf->video.cam.pos.y;
	pos.Z = gConf->video.cam.pos.z;
}

void Cam::setup () {
	// Setup camera for drawing
	glClear (GL_COLOR_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (FOV, 1, 1, renderDistance);
	gluLookAt (pos.X, pos.Y, pos.Z, sight.X, sight.Y, sight.Z, 0, 1, 0);
}

void Cam::accelerate (bool left, bool right, bool up, bool down) {
	// Accelerate camera if moving
	GLdouble moveSpeedMax = 10.0;    // TODO: move to config

	if (left && (moveSpeedX >= -moveSpeedMax))
		moveSpeedX -= 2 * moveAcceleration;
	if (right && (moveSpeedX <= moveSpeedMax))
		moveSpeedX += 2 * moveAcceleration;
	if (up && (moveSpeedY <= moveSpeedMax))
		moveSpeedY += 2 * moveAcceleration;
	if (down && (moveSpeedY >= -moveSpeedMax))
		moveSpeedY -= 2 * moveAcceleration;
}

void Cam::decelerate () {
	// Decelerate camera if stopping moving
	if (moveSpeedX < 0) moveSpeedX += moveAcceleration;
	if (moveSpeedX > 0) moveSpeedX -= moveAcceleration;
	if (moveSpeedY < 0) moveSpeedY += moveAcceleration;
	if (moveSpeedY > 0) moveSpeedY -= moveAcceleration;
}

void Cam::move () {
	pos.X += moveSpeedX;
	sight.X += moveSpeedX;
	pos.Y += moveSpeedY;
	sight.Y += moveSpeedY;
}