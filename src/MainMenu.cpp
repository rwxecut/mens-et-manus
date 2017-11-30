#include "MainMenu.h"


MainMenu::MainMenu () {
	// Create GUI
	LGUI = luaL_newstate ();
	luaL_openlibs (LGUI);
	lua::nk::init (LGUI);
	lua::game::init (LGUI);
}


MainMenu::~MainMenu () {
	lua_close (LGUI);
}


void MainMenu::update (WindowState *winState) {
	lua::nk::run (LGUI, winState->nkContext, MAINMENU_GUI_PATH);
}


void MainMenu::render () {
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}


void MainMenu::eventHandler (SDL_Event *event) {}
