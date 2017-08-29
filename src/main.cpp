#include "Game.h"

int main (int argc, char *args[]) {
	Config config;

	Game game(&config);
	game.mainLoop ();

	return 0;
}