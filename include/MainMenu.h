#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "Routine.h"
#include "windowState.h"
#include "auxiliary/game_lua.h"
#include "auxiliary/nk_lua.h"
#include "auxiliary/sdl_gl_overlay.h"

#define MAINMENU_GUI_PATH "../assets/mainMenu.lua"

class MainMenu : public Routine {
	lua_State *LGUI;
	Texture *background;

public:
	MainMenu (WindowState *winState);
	~MainMenu ();

	void update (WindowState *winState);
	void render ();
	void eventHandler (SDL_Event *event);
};
