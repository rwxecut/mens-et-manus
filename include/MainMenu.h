#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include "Routine.h"
#include "windowState.h"
#include "game_lua.h"
#include "nk_lua.h"

#define MAINMENU_GUI_PATH "../assets/mainMenu.lua"

class MainMenu : public Routine {
	lua_State *LGUI;

public:
	MainMenu ();
	~MainMenu ();

	void update (WindowState *winState);
	void render ();
	void eventHandler (SDL_Event *event);
};
