#pragma once

#include <SDL.h>
#include "LuaFile.h"
#include "Routine.h"
#include "Texture.h"
#include "Mod.h"


class MainMenu : public Routine {

	LuaFile *LGUI;
	Texture *background;
	ModList modList;

public:
	MainMenu ();
	~MainMenu ();

	void update ();
	void render ();
	void eventHandler (SDL_Event *event);
};
