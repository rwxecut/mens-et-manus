#include <Config.h>
#include "Game.h"


Game::Game ()
		: map (), cam () {
	// Create GUI
	LGUI = new LuaFile (GAME_GUI_PATH);
	lua::nk::bind (LGUI);
	lua::game::bind (LGUI);
	// Initially set visible tiles
	cam.setup ();
	map.setVisibleTiles (config.screen.size);
}


Game::~Game () {}


void Game::update (WindowState *winState) {
	keyHandler ();
	SDL_GetMouseState (&mousePos.x, &mousePos.y);
	mousePositionHandler (winState);
	if (cam.moveSpeed != vector2d<GLdouble>{0, 0})
		cam.decelerate ();
	// cam.moveSpeed has changed, so we have to recheck
	if (cam.moveSpeed != vector2d<GLdouble>{0, 0}) {
		cam.move ();
		map.setVisibleTiles (config.screen.size);
	}

	map.setSelectedTile (mousePos);

	lua::nk::run (LGUI, winState->nkContext);
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
	direction_t dir = {(mousePos.x < map.mouseMoveArea),
	                   (mousePos.x > config.screen.size.width - map.mouseMoveArea),
	                   (mousePos.y < map.mouseMoveArea),
	                   (mousePos.y > config.screen.size.height - map.mouseMoveArea)};
	cam.accelerate (&dir);
}


void Game::eventHandler (SDL_Event *event) {
	switch (event->type) {
		case SDL_MOUSEWHEEL:
			cam.zoom (event->wheel.y);
			map.setVisibleTiles (config.screen.size);
			break;
		default:;
	}
}
