#include "routines/Game.h"
#include "Config.h"
#include "lib/nuklear/nuklear_common.h"
#include "lua_binders/nk_lua.h"
#include "lua_binders/game_lua.h"

#include "lib/glm/vec2.hpp"
#include "lib/glm/mat4x4.hpp"


Game::Game ()
		: cam (), map (&cam) {
	// Create GUI
	LGUI = new LuaFile (config.path.gameMenuGUI.c_str ());
	lua::nk::bind (LGUI);
	lua::game::bind (LGUI);
	// Initially set visible tiles
	cam.setup (NULL);
	map.setVisibleTiles (glm::ivec2 (config.screen.size.width, config.screen.size.height));
}


Game::~Game () {}


void Game::update () {
	keyHandler ();
	SDL_GetMouseState (&mousePos.x, &mousePos.y);
	mousePositionHandler ();
	if (cam.moveSpeed != glm::vec3 (0))
		cam.decelerate ();
	// cam.moveSpeed has changed, so we have to recheck
	if (cam.moveSpeed != glm::vec3 (0)) {
		cam.move ();
		map.setVisibleTiles (glm::ivec2 (config.screen.size.width, config.screen.size.height));
	}
	map.setSelectedTile (glm::ivec2 (mousePos.x, mousePos.y));

	lua::nk::run (LGUI);
}


void Game::render () {
	// TODO: create MapRenderer class and move cam to it
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glm::mat4 MVP;
	cam.setup (&MVP);
	map.draw (MVP);
}


void Game::keyHandler () {
	const uint8_t *keystates = SDL_GetKeyboardState (NULL);
	direction_t dir = {keystates[SDL_SCANCODE_LEFT], keystates[SDL_SCANCODE_RIGHT],
	                   keystates[SDL_SCANCODE_UP], keystates[SDL_SCANCODE_DOWN]};
	cam.accelerate (&dir);
}


void Game::mousePositionHandler () {
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
			map.setVisibleTiles (glm::ivec2 (config.screen.size.width, config.screen.size.height));
			break;
		default:;
	}
}
