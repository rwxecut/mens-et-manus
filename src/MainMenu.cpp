#include "MainMenu.h"
#include <SDL_image.h>
#include "Config.h"
#include "lib/nuklear/nuklear_common.h"
#include "lua_binders/game_lua.h"
#include "lua_binders/nk_lua.h"
#include "lua_binders/modlist_lua.h"


MainMenu::MainMenu () {
	// Create GUI
	LGUI = new LuaFile (config.path.mainMenuGUI.c_str ());
	lua::nk::bind (LGUI);
	lua::game::bind (LGUI);
	lua::modlist::init (&modList);
	lua::modlist::bind (LGUI);

	// Load background
	std::string bgPath = LGUI->state["background"];
	background = new Texture (bgPath.c_str ());

	// Load mods list
	modList.load ();
	LGUI->call ("loadModList");
}


MainMenu::~MainMenu () {
	delete background;
}


void MainMenu::update () {
	lua::nk::run (LGUI);
}


void MainMenu::render () {
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	//@formatter:off
	GLfloat vertex[] = {-1,  1, 0,
	                    -1, -1, 0,
	                     1, -1, 0,
	                     1,  1, 0};
	GLfloat texCoords[] = {0, 0,
	                       0, 1,
	                       1, 1,
	                       1, 0};
	//@formatter:on
	background->stateDraw (GL_QUADS, 4, vertex, texCoords);
}


void MainMenu::eventHandler (SDL_Event *event) {}
