#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "Routine.h"
#include "windowState.h"
#include "game_lua.h"
#include "nk_lua.h"
#include "sdl_gl_overlay.h"

#define MAINMENU_GUI_PATH "../assets/mainMenu.lua"

class MainMenu : public Routine {
	lua_State *LGUI;
	GLtexture tex;

public:
	MainMenu ();
	~MainMenu ();
	void loadTestTex();

	void update (WindowState *winState);
	void render ();
	void eventHandler (SDL_Event *event);
};
