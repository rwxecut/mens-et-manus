#pragma once

#include <SDL.h>
#include "engine/LuaFile.h"
#include "engine/Mod.h"
#include "client/routines/Routine.h"
#include "client/Texture.h"
#include "client/Shader.h"
#include "auxiliary/primitives.h"


class MainMenu : public Routine {

	lua::File *LGUI;
	Mod::List modList;

	gl::RectPtr bgRect;
	TexturePtr background;
	ShaderProgramPtr shaderProg;

public:
	MainMenu ();

	void update ();
	void render ();
	void eventHandler (SDL_Event *event);
};
