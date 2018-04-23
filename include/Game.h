#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include "auxiliary/nk_lua.h"
#include "auxiliary/game_lua.h"

#include "LuaFile.h"
#include "Routine.h"
#include "windowState.h"
#include "Map.h"
#include "Cam.h"

#define GAME_GUI_PATH "../assets/gameMenu.lua"

class Game : public Routine {

	Map map;
	Cam cam;
	LuaFile *LGUI;

	void keyHandler ();
	void mousePositionHandler (WindowState *winState);

public:
	Game (Config *config, WindowState *winState, RoutineHandler *routineHandler);
	~Game ();

	void update (WindowState *winState);
	void render ();
	void eventHandler (SDL_Event *event);
};
