#include "routines/MainMenu.h"
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

	// Create shader program
	const char *vertShaderPath = ((std::string) LGUI->state["vertShader"]).c_str ();
	const char *fragShaderPath = ((std::string) LGUI->state["fragShader"]).c_str ();
	shaderProg = new ShaderProgram ("MainMenu", Shader::fromFile, vertShaderPath, Shader::fromFile, fragShaderPath);

	// Bind texture unit
	shaderProg->use ();
	shaderProg->setUniform ("background", 0);

	//@formatter:off
	GLfloat vertices[] = {
	//		 x   y  s  t
			-1,  1, 0, 1,
			-1, -1, 0, 0,
			 1, -1, 1, 0,
			 1,  1, 1, 1
	};
	//@formatter:on
	bgRect = new gl::Rect (GL_STATIC_DRAW, vertices, sizeof (vertices));
	bgRect->setAttributes (0, 2, 4, 0); // X, Y
	bgRect->setAttributes (1, 2, 4, 2); // S, T
}


MainMenu::~MainMenu () {
	delete background;
	delete shaderProg;
	delete bgRect;
}


void MainMenu::update () {
	lua::nk::run (LGUI);
}


void MainMenu::render () {
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	background->bind (0);
	shaderProg->use ();
	bgRect->draw ();
}


void MainMenu::eventHandler (SDL_Event *event) {}
