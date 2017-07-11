#include "Game.h"

int main (int argc, char *args[]) {

	GameConfig const *gConf = new GameConfig ();

	Game game (gConf);
	game.mainLoop ();

	return 0;
}