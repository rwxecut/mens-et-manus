#include "Game.h"

Game::Game (Config *config)
		: cam (config) {
}


void Game::update (int mouseX, int mouseY) {
	if (cam.moveSpeed.x != 0 || cam.moveSpeed.y != 0)
		cam.decelerate ();
	cam.move ();

	GLdouble unprojX, unprojY;
	unproject (mouseX, mouseY, &unprojX, &unprojY);
	map.getHoveredTile (unprojX, unprojY);
}


void Game::render () {
	cam.setup ();
	map.draw ();
}


void Game::unproject (GLdouble srcX, GLdouble srcY,
                      GLdouble *objX, GLdouble *objY) {
	GLdouble modelview[16], projection[16];
	GLint viewport[4];
	GLfloat srcZ;
	GLdouble objZ;

	glGetDoublev (GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev (GL_PROJECTION_MATRIX, projection);
	glGetIntegerv (GL_VIEWPORT, viewport);
	srcY = (GLfloat) (viewport[3] - srcY);
	glReadPixels ((GLint) srcX, (GLint) srcY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &srcZ);
	gluUnProject (srcX, srcY, srcZ, modelview, projection, viewport, objX, objY, &objZ);
}


void Game::keyHandler (const uint8_t *keystates) {
	cam.accelerate (keystates[SDL_SCANCODE_LEFT], keystates[SDL_SCANCODE_RIGHT],
	                keystates[SDL_SCANCODE_UP], keystates[SDL_SCANCODE_DOWN]);
}


void Game::mousePositionHandler (int scrWidth, int scrHeight, int mouseX, int mouseY) {
	static const int moveMapArea = 40;

	// @formatter:off
	cam.accelerate ((mouseX < moveMapArea),
	                (mouseX > scrWidth - moveMapArea),
	                (mouseY < moveMapArea),
	                (mouseY > scrHeight - moveMapArea));
	// @formatter:on
}


void Game::mouseScrollHandler (int32_t delta) {
	cam.zoom (delta);
}
