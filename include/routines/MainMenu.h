#pragma once

#include <SDL.h>
#include "Shader.h"
#include "LuaFile.h"
#include "Routine.h"
#include "Texture.h"
#include "Mod.h"
#include "auxiliary/primitives.h"


class MainMenu : public Routine {

	LuaFile *LGUI;
	ModList modList;

	gl::Rect *bgRect;
	Texture *background;
	ShaderProgram *shaderProg;

public:
	MainMenu ();
	~MainMenu ();

	void update ();
	void render ();
	void eventHandler (SDL_Event *event);
};
