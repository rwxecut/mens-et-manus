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

	map.setSelectedTile (winState->mousePos);
	map.setVisibleTiles (winState->screenSize);

	lua::nk::run (LGUI, winState->nkContext, GAME_GUI_PATH);
}


void Game::render () {
	cam.setup ();
	map.draw ();
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
