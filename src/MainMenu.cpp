#include "MainMenu.h"


MainMenu::MainMenu (WindowState *winState) {
	// Create GUI
	LGUI = new LuaFile (MAINMENU_GUI_PATH);
	lua::nk::init (LGUI);
	lua::game::init (LGUI, winState);

	LGUI->run ();
	char *bgPath = LGUI->getValue<char *> ("background", Scope::global);
	background = new Texture (bgPath);
}


MainMenu::~MainMenu () {
	delete background;
	delete LGUI;
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
