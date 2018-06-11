#include "MainMenu.h"


MainMenu::MainMenu () {
	// Create GUI
	LGUI = new LuaFile (MAINMENU_GUI_PATH);
	lua::nk::bind (LGUI);
	lua::game::bind (LGUI);

	std::string bgPath = LGUI->state["background"];
	background = new Texture (bgPath.c_str ());
}


MainMenu::~MainMenu () {
	delete background;
}


void MainMenu::update (WindowState *winState) {
	lua::nk::run (LGUI, winState->nkContext);
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
