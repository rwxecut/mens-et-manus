#include "MainMenu.h"


MainMenu::MainMenu (WindowState *winState) {
	// Create GUI
	LGUI = luaL_newstate ();
	luaL_openlibs (LGUI);
	lua::nk::init (LGUI);
	lua::game::init (LGUI, winState);

	background = new Texture ();
	if (!background->load ("../assets/thinking.png")) ;
}


MainMenu::~MainMenu () {
	delete background;
	lua_close (LGUI);
}


void MainMenu::update (WindowState *winState) {
	lua::nk::run (LGUI, winState->nkContext, MAINMENU_GUI_PATH);
}


void MainMenu::render () {
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	//@formatter:off
	GLint vertices[] = {-1, -1,
	                     1, -1,
			             1,  1,
			            -1,  1};
	GLint texVertices[] = {0, 1,
	                       1, 1,
	                       1, 0,
	                       0, 0};
	//@formatter:on
	background->draw (vertices, texVertices);
}


void MainMenu::eventHandler (SDL_Event *event) {}
