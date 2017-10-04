#include "Game.h"


Game::Game (Config *config)
		: cam (config) {
}


void Game::update (point2d<int> mousePos) {
	if (cam.moveSpeed.x != 0 || cam.moveSpeed.y != 0)
		cam.decelerate ();
	cam.move ();

	point2d<GLdouble> unprojection;
	unproject ({(GLdouble) mousePos.x, (GLdouble) mousePos.y}, &unprojection);
	map.getHoveredTile (unprojection);
}


void Game::render () {
	cam.setup ();
	map.draw ();
}


void Game::unproject (point2d<GLdouble> source, point2d<GLdouble> *object) {
	GLdouble modelview[16], projection[16];
	GLint viewport[4];
	GLfloat srcZ;
	GLdouble objZ;

	glGetDoublev (GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev (GL_PROJECTION_MATRIX, projection);
	glGetIntegerv (GL_VIEWPORT, viewport);
	source.y = (GLfloat) (viewport[3] - source.y);
	glReadPixels ((GLint) source.x, (GLint) source.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &srcZ);
	gluUnProject (source.x, source.y, srcZ, modelview, projection, viewport, &object->x, &object->y, &objZ);
}


void Game::keyHandler (const uint8_t *keystates) {
	direction_t dir = {keystates[SDL_SCANCODE_LEFT], keystates[SDL_SCANCODE_RIGHT],
	                   keystates[SDL_SCANCODE_UP], keystates[SDL_SCANCODE_DOWN]};
	cam.accelerate (&dir);
}


void Game::mousePositionHandler (size2d<int> screenSize, point2d<int> mousePos) {
	static const int moveMapArea = 40;

	direction_t dir = {(mousePos.x < moveMapArea),
	                   (mousePos.x > screenSize.width - moveMapArea),
	                   (mousePos.y < moveMapArea),
	                   (mousePos.y > screenSize.height - moveMapArea)};
	cam.accelerate (&dir);
}


void Game::mouseScrollHandler (int32_t delta) {
	cam.zoom (delta);
}
