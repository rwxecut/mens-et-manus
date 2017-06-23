#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#include "mouse.h"
#include "GameConfig.h"

extern GameConfig const *GCONF;

namespace mapPrivate { // TODO: Replace with camera class
	GLdouble moveSpeedX, moveSpeedY;
	void camAccelerate (bool left, bool right, bool up, bool down, GLfloat accelMultiplier);
	void camDecelerate ();
	void camMove ();
}

namespace map {

	struct {
		GLdouble FOV;
		GLdouble renderDistance;
		struct {
			GLdouble X, Y, Z;
		} pos;
		struct {
			GLdouble X = 0, Y = 0, Z = 0;
		} sight;
	} cam; // TODO: remake into a class

	void Init () {
		glLineWidth (2.0);    // temp
		glColor3f (0.1, 0.8, 0.8);    // temp

		// Init camera values from config
		cam.FOV = GCONF->video.cam.fov;
		cam.renderDistance = GCONF->video.cam.renderDistance;
		cam.pos.X = GCONF->video.cam.pos.x;
		cam.pos.Y = GCONF->video.cam.pos.y;
		cam.pos.Z = GCONF->video.cam.pos.z;
	}

	void Draw () {
		// Setup camera
		glClear (GL_COLOR_BUFFER_BIT);
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		gluPerspective (cam.FOV, 1, 1, cam.renderDistance);
		gluLookAt (cam.pos.X, cam.pos.Y, cam.pos.Z, cam.sight.X, cam.sight.Y, cam.sight.Z, 0, 1, 0);

		// Draw hexagons (temp)
		int hexnum = 5;
		GLfloat hex_l = 100.f;
		GLfloat hex_r = hex_l * 0.866f; // 3*sqrt(3)
		glEnableClientState (GL_VERTEX_ARRAY);
		for (int i = -hexnum; i <= hexnum; i++) {
			GLfloat dy = i * hex_l * 3 / 2;
			for (int j = -hexnum; j <= hexnum; j++) {
				GLfloat dx = j * 2 * hex_r + (i & 1) * hex_r;
				// @formatter:off
				GLfloat vertices[] = {	-hex_r + dx, -hex_l/2 + dy, 0.f,
										 00.0f + dx, -hex_l   + dy, 0.f,
										 hex_r + dx, -hex_l/2 + dy, 0.f,
										 hex_r + dx,  hex_l/2 + dy, 0.f,
										 00.0f + dx,  hex_l   + dy, 0.f,
										-hex_r + dx,  hex_l/2 + dy, 0.f};
				// @formatter:on
				glVertexPointer (3, GL_FLOAT, 0, vertices);
				glDrawArrays (GL_LINE_LOOP, 0, 6);
			}
		}
		glDisableClientState (GL_VERTEX_ARRAY);
	}

	void Update () {
		if (mapPrivate::moveSpeedX != 0 || mapPrivate::moveSpeedY != 0)
			mapPrivate::camDecelerate ();
		mapPrivate::camMove ();
	}

	void MousePositionHandler () {
		int mouseZoneMoveMap = 40;
		GLfloat mouse_camAccelMultiplier = 2.0;    // TODO: move to config
		SDL_GetMouseState (&mouse.x, &mouse.y);
		// @formatter:off
		mapPrivate::camAccelerate ((mouse.x < mouseZoneMoveMap),
								   (mouse.x > GCONF->screen.width - mouseZoneMoveMap),
								   (mouse.y < mouseZoneMoveMap),
								   (mouse.y > GCONF->screen.height - mouseZoneMoveMap),
									mouse_camAccelMultiplier);
		// @formatter:on
	}

	void MouseScrollHandler (int32_t delta) {
		GLdouble scrollSpeed = 20.0;      //
		GLdouble minZ = 200.0;            // TODO: move to config
		GLdouble maxZ = 700.0;            //
		if ((delta > 0 && cam.pos.Z < maxZ) || (delta < 0 && cam.pos.Z > minZ))
			cam.pos.Z += delta * scrollSpeed;
	}

	void KeyHandler (SDL_Keycode key) {
		GLfloat key_camAccelMultiplier = 10.0;
		mapPrivate::camAccelerate ((key == SDLK_LEFT), (key == SDLK_RIGHT),
								   (key == SDLK_UP), (key == SDLK_DOWN), key_camAccelMultiplier);
	}
}

namespace mapPrivate {

	GLdouble moveAcceleration = 0.5;    // TODO: move to config

	void camAccelerate (bool left, bool right, bool up, bool down, GLfloat accelMultiplier) {
		GLdouble moveSpeedMax = 10.0;    // TODO: move to config

		if (left && (moveSpeedX >= -moveSpeedMax))
			moveSpeedX -= accelMultiplier * moveAcceleration;
		if (right && (moveSpeedX <= moveSpeedMax))
			moveSpeedX += accelMultiplier * moveAcceleration;
		if (up && (moveSpeedY <= moveSpeedMax))
			moveSpeedY += accelMultiplier * moveAcceleration;
		if (down && (moveSpeedY >= -moveSpeedMax))
			moveSpeedY -= accelMultiplier * moveAcceleration;
	}

	void camDecelerate () {
		if (moveSpeedX < 0) moveSpeedX += moveAcceleration;
		if (moveSpeedX > 0) moveSpeedX -= moveAcceleration;
		if (moveSpeedY < 0) moveSpeedY += moveAcceleration;
		if (moveSpeedY > 0) moveSpeedY -= moveAcceleration;
	}

	void camMove () {
		map::cam.pos.X += moveSpeedX;
		map::cam.sight.X += moveSpeedX;
		map::cam.pos.Y += moveSpeedY;
		map::cam.sight.Y += moveSpeedY;
	}
}