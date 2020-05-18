#pragma once

#include <SDL.h>
#include "Shader.h"
#include "LuaFile.h"
#include "Routine.h"
#include "Texture.h"
#include "Mod.h"
#include "auxiliary/primitives.h"


class MainMenu : public Routine {

	lua::File *LGUI;
	ModList modList;

	gl::RectPtr bgRect;
	TexturePtr background;
	ShaderProgramPtr shaderProg;

public:
	MainMenu ();

	void update ();
	void render ();
	void eventHandler (SDL_Event *event);
};
