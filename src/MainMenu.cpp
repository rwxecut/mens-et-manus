#include "MainMenu.h"


MainMenu::MainMenu () {
	// Create GUI
	LGUI = luaL_newstate ();
	luaL_openlibs (LGUI);
	lua::nk::init (LGUI);
	lua::game::init (LGUI);
}


void MainMenu::loadTestTex () {
	sdl_gl::loadTexture (&tex, "../assets/thinking.png");
}


MainMenu::~MainMenu () {
	glDeleteTextures (1, &tex);
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

	glBindTexture (GL_TEXTURE_2D, tex);
	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY);
	glVertexPointer (2, GL_INT, 0, vertices);
	glTexCoordPointer (2, GL_INT, 0, texVertices);
	glDrawArrays (GL_QUADS, 0, 4);
	glDisableClientState (GL_TEXTURE_COORD_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);
}


void MainMenu::eventHandler (SDL_Event *event) {}
