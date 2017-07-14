#include "Save.h"
#include "Game.h"
#include "GameConfig.h"
#include <SDL.h>

int main (int argc, char *args[]) {

	GameConfig const gConf;
	Save save;

	Game game (&gConf, &save);
	game.mainLoop ();

	return 0;
}