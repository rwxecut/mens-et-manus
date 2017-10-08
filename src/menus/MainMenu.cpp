#include "menus/MainMenu.h"


MainMenu::MainMenu () {
	;
}


void MainMenu::eventHandler (SDL_Event *event) {
	switch (event->type) {
		default:;
	}
}


void MainMenu::update (WindowState *winState) {
	;
}


void MainMenu::render () {
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
}
