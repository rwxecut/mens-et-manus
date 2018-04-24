#include "Game.h"


Game::Game (Config *config, WindowState *winState, RoutineHandler *routineHandler)
		: map (), cam (config) {
	// Create GUI
	LGUI = new LuaFile (GAME_GUI_PATH);
	lua::nk::init (LGUI);
	lua::game::init (LGUI, routineHandler);
	LGUI->run ();
	// Initially set visible tiles
	cam.setup ();
	map.setVisibleTiles (winState->screenSize);
}


Game::~Game () {
	delete LGUI;
}


void Game::update (WindowState *winState) {
	keyHandler ();
	SDL_GetMouseState (&mousePos.x, &mousePos.y);
	mousePositionHandler (winState);
	if (cam.moveSpeed != vector2d<GLdouble>{0, 0})
		cam.decelerate ();
	// cam.moveSpeed has changed, so we have to recheck
	if (cam.moveSpeed != vector2d<GLdouble>{0, 0}) {
		cam.move ();
		map.setVisibleTiles (winState->screenSize);
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
	                   (mousePos.x > winState->screenSize.width - map.mouseMoveArea),
	                   (mousePos.y < map.mouseMoveArea),
	                   (mousePos.y > winState->screenSize.height - map.mouseMoveArea)};
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
