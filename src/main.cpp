#include <SDL.h>
#include "Viewport.h"

int main (int argc, char *args[]) {

	GameConfig const *gConf = new GameConfig ();

	Viewport VP (gConf);
	VP.mainLoop ();

	return 0;
}