#include "MainMenu.h"


MainMenu::MainMenu () {
	// Create GUI
	LGUI = new LuaFile (config.path.mainMenuGUI.c_str ());
	lua::nk::bind (LGUI);
	lua::game::bind (LGUI);

	// Load background
	std::string bgPath = LGUI->state["background"];
	background = new Texture (bgPath.c_str ());

	// Load mods list
	loadModList ();
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


void MainMenu::loadModList () {
	for (auto &dir: fs::directory_iterator (config.path.assets))
		if (fs::is_directory (dir)) {
			fs::path modFilePath = dir.path () / config.path.modfile;
			if (fs::exists (modFilePath)) {
				// mingw does some shit with fs::path.c_str()
				LuaFile modFile (modFilePath.string ().c_str ());
				std::string modName = modFile.state["name"];
				std::string modVersion = modFile.state["version"];
				logger.write ("Mod found: %s %s\n", modName.c_str (), modVersion.c_str ());
			}
		}
}
