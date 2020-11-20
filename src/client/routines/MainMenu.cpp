#include "client/routines/MainMenu.h"
#include "lib/nuklear/nuklear_common.h"
#include "engine/Config.h"

#include "lua_binders/buffer_lua.h"
#include "lua_binders/log_lua.h"
#include "lua_binders/game_lua.h"
#include "lua_binders/nk_lua.h"
#include "lua_binders/modlist_lua.h"


MainMenu::MainMenu () {
	// Create GUI
	LGUI = new lua::File (config.path.mainMenuGUI.c_str ());
	LGUI->addBind<lua::bind::Game> ("game");
	LGUI->addBind<lua::bind::Modlist> ("mods", &modList);
	LGUI->addBind<lua::bind::DataBuffer> ("buffer");
	LGUI->addBind<lua::bind::Log> ("log");
	LGUI->addBind<lua::bind::Nuklear> ("gui");

	// Load background
	std::string bgPath = LGUI->state["background"];
	background = std::make_unique<Texture> (bgPath.c_str ());

	// Load mods list
	modList.load ();
	LGUI->call ("loadModList");

	// Create shader program
	std::string vertShaderPath = LGUI->state["vertShader"];
	std::string fragShaderPath = LGUI->state["fragShader"];
	shaderProg = std::make_unique<ShaderProgram> ("MainMenu", Shader::fromFile, vertShaderPath.c_str(),
			Shader::fromFile, fragShaderPath.c_str());

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
	bgRect = std::make_unique<gl::Rect> (GL_STATIC_DRAW, vertices, sizeof (vertices));
	bgRect->setAttributes (0, 2, 4, 0); // X, Y
	bgRect->setAttributes (1, 2, 4, 2); // S, T
}


void MainMenu::update () {
	LGUI->call ("render");
}


void MainMenu::render () {
	glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	background->bind (0);
	shaderProg->use ();
	bgRect->draw ();
}


void MainMenu::eventHandler (SDL_Event *event) {}
