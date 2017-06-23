#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#include "map.h"
#include "mouse.h"
#include "GameConfig.h"

extern GameConfig const *GCONF;

namespace map {

	class cam_c {
	public:
		// General variables & methods
		GLdouble FOV;
		GLdouble renderDistance;
		struct {
			GLdouble X, Y, Z;
		} pos;
		struct {
			GLdouble X = 0, Y = 0, Z = 0;
		} sight;
		void init ();
		void setup ();

		// Moving variables & methods
		GLdouble moveSpeedX, moveSpeedY;
		GLdouble moveAcceleration = 0.5;    // TODO: move to config
		void accelerate (bool left, bool right, bool up, bool down);
		void decelerate ();
		void move ();
	} cam;

	void Init () {
		glLineWidth (2.0);    // temp
		glColor3f (0.1, 0.8, 0.8);    // temp

		cam.init ();
	}

	void Draw () {
		cam.setup ();

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
		KeyHandler ();
		if (cam.moveSpeedX != 0 || cam.moveSpeedY != 0)
			cam.decelerate ();
		cam.move ();
	}

	void MousePositionHandler () {
		int mouseZoneMoveMap = 40; // TODO: move to config
		SDL_GetMouseState (&mouse.x, &mouse.y);
		// @formatter:off
		cam.accelerate ((mouse.x < mouseZoneMoveMap),
						(mouse.x > GCONF->screen.width - mouseZoneMoveMap),
						(mouse.y < mouseZoneMoveMap),
						(mouse.y > GCONF->screen.height - mouseZoneMoveMap));
		// @formatter:on
	}

	void MouseScrollHandler (int32_t delta) {
		GLdouble scrollSpeed = 20.0;      //
		GLdouble minZ = 200.0;            // TODO: move to config
		GLdouble maxZ = 700.0;            //
		if ((delta > 0 && cam.pos.Z < maxZ) || (delta < 0 && cam.pos.Z > minZ))
			cam.pos.Z += delta * scrollSpeed;
	}

	void KeyHandler () {
		const uint8_t *keystates = SDL_GetKeyboardState (NULL);
		cam.accelerate (keystates[SDL_SCANCODE_LEFT], keystates[SDL_SCANCODE_RIGHT],
						keystates[SDL_SCANCODE_UP], keystates[SDL_SCANCODE_DOWN]);
	}

	void cam_c::init () {
		// Init camera values from config
		FOV = GCONF->video.cam.fov;
		renderDistance = GCONF->video.cam.renderDistance;
		pos.X = GCONF->video.cam.pos.x;
		pos.Y = GCONF->video.cam.pos.y;
		pos.Z = GCONF->video.cam.pos.z;
	}

	void cam_c::setup () {
		// Setup camera for drawing
		glClear (GL_COLOR_BUFFER_BIT);
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		gluPerspective (FOV, 1, 1, renderDistance);
		gluLookAt (pos.X, pos.Y, pos.Z, sight.X, sight.Y, sight.Z, 0, 1, 0);
	}

	void cam_c::accelerate (bool left, bool right, bool up, bool down) {
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

	void cam_c::decelerate () {
		// Decelerate camera if stopping moving
		if (moveSpeedX < 0) moveSpeedX += moveAcceleration;
		if (moveSpeedX > 0) moveSpeedX -= moveAcceleration;
		if (moveSpeedY < 0) moveSpeedY += moveAcceleration;
		if (moveSpeedY > 0) moveSpeedY -= moveAcceleration;
	}

	void cam_c::move () {
		pos.X += moveSpeedX;
		sight.X += moveSpeedX;
		pos.Y += moveSpeedY;
		sight.Y += moveSpeedY;
	}
}