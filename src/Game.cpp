#include "Game.h"


Game::Game (Config *config, WindowState *winState)
		: map (), cam (config) {
	// Create GUI
	LGUI = luaL_newstate ();
	luaL_openlibs (LGUI);
	lua::nk::init (LGUI);
	lua::game::init (LGUI, winState);
}


Game::~Game () {
	lua_close (LGUI);
}


void Game::update (WindowState *winState) {
	keyHandler ();
	mousePositionHandler (winState);
	if (cam.moveSpeed.x != 0 || cam.moveSpeed.y != 0)
		cam.decelerate ();
	cam.move ();

	point2d<GLdouble> unprojection;
	unproject ({(GLdouble) winState->mousePos.x, (GLdouble) winState->mousePos.y}, &unprojection);
	map.getHoveredTile (unprojection);

	lua::nk::run (LGUI, winState->nkContext, GAME_GUI_PATH);
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


void Game::keyHandler () {
	const uint8_t *keystates = SDL_GetKeyboardState (NULL);
	direction_t dir = {keystates[SDL_SCANCODE_LEFT], keystates[SDL_SCANCODE_RIGHT],
	                   keystates[SDL_SCANCODE_UP], keystates[SDL_SCANCODE_DOWN]};
	cam.accelerate (&dir);
}


void Game::mousePositionHandler (WindowState *winState) {
	direction_t dir = {(winState->mousePos.x < map.mouseMoveArea),
	                   (winState->mousePos.x > winState->screenSize.width - map.mouseMoveArea),
	                   (winState->mousePos.y < map.mouseMoveArea),
	                   (winState->mousePos.y > winState->screenSize.height - map.mouseMoveArea)};
	cam.accelerate (&dir);
}


void Game::eventHandler (SDL_Event *event) {
	switch (event->type) {
		case SDL_MOUSEWHEEL:
			cam.zoom (event->wheel.y);
			break;
		default:;
	}
}
