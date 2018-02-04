#include "MainMenu.h"


MainMenu::MainMenu (WindowState *winState) {
	// Create GUI
	LGUI = luaL_newstate ();
	luaL_openlibs (LGUI);
	lua::nk::init (LGUI);
	lua::game::init (LGUI, winState);

	background = new Texture ("../assets/thinking.png");
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
