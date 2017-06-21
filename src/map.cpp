#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>
#include <mouse.h>

#include "mouse.h"
#include "GameConfig.h"

extern GameConfig const *GCONF;

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
	} cam;

	void Init () {
		glLineWidth (2.0);
		glColor3f (0.1, 0.8, 0.8);

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

		// Draw hexagons
		GLfloat hex_l = 100.f;
		GLfloat hex_r = hex_l * 0.866f; // 3*sqrt(3)
		glEnableClientState (GL_VERTEX_ARRAY);
		for (int i = -2; i <= 2; i++) {
			GLfloat dy = i * hex_l * 3 / 2;
			for (int j = -2; j <= 2; j++) {
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

	void MousePositionHandler () {
		int mouseZoneMoveMap = 40;
		int moveDelta = 5;
		SDL_GetMouseState (&mouse.x, &mouse.y);
		if (mouse.x < mouseZoneMoveMap) {
			cam.pos.X -= moveDelta;
			cam.sight.X -= moveDelta;
		}
		if (mouse.x > GCONF->screen.width - mouseZoneMoveMap) {
			cam.pos.X += moveDelta;
			cam.sight.X += moveDelta;
		}
		if (mouse.y < mouseZoneMoveMap) {
			cam.pos.Y += moveDelta;
			cam.sight.Y += moveDelta;
		}
		if (mouse.y > GCONF->screen.height - mouseZoneMoveMap) {
			cam.pos.Y -= moveDelta;
			cam.sight.Y -= moveDelta;
		}
	}

	void MouseScrollHandler (int32_t delta) {
		GLdouble scrollSpeed = 20.0;
		GLdouble minZ = 200.0;
		GLdouble maxZ = 700.0;
		if ((delta > 0 && cam.pos.Z < maxZ) || (delta < 0 && cam.pos.Z > minZ))
			cam.pos.Z += delta * scrollSpeed;
	}

	void KeyHandler (SDL_Keycode key) {
		;
	}
}