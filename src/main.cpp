#include "Window.h"


int main (int argc, char *args[]) {
	Config config;

	Window window (&config);
	window.mainLoop ();

	return 0;
}
