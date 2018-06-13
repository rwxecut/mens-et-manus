#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "Config.h"
#include "LuaFile.h"
#include "Routine.h"
#include "Texture.h"
#include "windowState.h"
#include "auxiliary/filesystem.h"
#include "auxiliary/game_lua.h"
#include "auxiliary/nk_lua.h"


class MainMenu : public Routine {

	LuaFile *LGUI;
	Texture *background;

public:
	MainMenu ();
	~MainMenu ();

	void loadModList ();

	void update (WindowState *winState);
	void render ();
	void eventHandler (SDL_Event *event);
};
