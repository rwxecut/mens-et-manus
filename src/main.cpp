#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
#include <cstdio>

#include "Mouse.h"
#include "Viewport.h"
#include "GameConfig.h"
#include "main_menu.h"
#include "Map.h"

int main (int argc, char *args[]) {

	GameConfig const *gConf = new GameConfig ();

	Viewport VP (gConf);
	VP.mainLoop ();

	return 0;
}