#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "Config.h"
#include "LuaFile.h"
#include "Routine.h"
#include "Texture.h"
#include "Mod.h"
#include "nuklear/nuklear_common.h"
#include "auxiliary/game_lua.h"
#include "auxiliary/nk_lua.h"


class MainMenu : public Routine {

	LuaFile *LGUI;
	Texture *background;
	ModList modList;

public:
	MainMenu ();
	~MainMenu ();

	void update (nk_context *nkContext);
	void render ();
	void eventHandler (SDL_Event *event);
};
