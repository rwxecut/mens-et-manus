#pragma once

#include <SDL.h>
#include "LuaFile.h"
#include "Routine.h"
#include "Map.h"
#include "Cam.h"
#include "auxiliary/geometry.h"


class Game : public Routine {

	Map map;
	Cam cam;
	lua::File *LGUI;

	point2d<int> mousePos;

	void keyHandler ();
	void mousePositionHandler ();

public:
	Game ();
	~Game ();

	void update ();
	void render ();
	void eventHandler (SDL_Event *event);
};
