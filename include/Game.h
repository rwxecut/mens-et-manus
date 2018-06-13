#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include "auxiliary/nk_lua.h"
#include "auxiliary/game_lua.h"

#include <Config.h>
#include "LuaFile.h"
#include "Routine.h"
#include "nuklear/nuklear_common.h"
#include "Map.h"
#include "Cam.h"
#include "auxiliary/geometry.h"


class Game : public Routine {

	Map map;
	Cam cam;
	LuaFile *LGUI;

	point2d<int> mousePos;

	void keyHandler ();
	void mousePositionHandler ();

public:
	Game ();
	~Game ();

	void update (nk_context *nkContext);
	void render ();
	void eventHandler (SDL_Event *event);
};
