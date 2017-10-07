#include "menus/MainMenu.h"

MainMenu::MainMenu () {
	;
}


void MainMenu::keyHandler (const uint8_t *keystates) {
	;
}


void MainMenu::mousePositionHandler (size2d<int> screenSize, point2d<int> mousePos) {
	;
}


void MainMenu::mouseScrollHandler (int32_t delta) {
	;
}


void MainMenu::update (point2d<int> mousePos) {
	;
}


void MainMenu::render () {
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
}
