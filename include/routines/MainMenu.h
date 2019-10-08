#pragma once

#include <SDL.h>
#include "Shader.h"
#include "LuaFile.h"
#include "Routine.h"
#include "Texture.h"
#include "Mod.h"
#include "auxiliary/primitives.h"

#include <memory>


class MainMenu : public Routine {

	LuaFile *LGUI;
	ModList modList;

	gl::RectPtr bgRect;
	std::unique_ptr<Texture> background;
	ShaderProgramPtr shaderProg;

public:
	MainMenu ();

	void update ();
	void render ();
	void eventHandler (SDL_Event *event);
};
