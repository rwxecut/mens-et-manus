#define VERSION "v. dev0"

#include "auxiliary/logger_implenent.h"
#include "Config.h"
#include "Window.h"


int main (int argc, char *args[]) {
	logger.write ("Mens et Manus " VERSION);

	Config config;

	Window window (&config);
	window.mainLoop ();

	return 0;
}
