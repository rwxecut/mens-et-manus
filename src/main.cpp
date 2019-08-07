#define VERSION "v. dev0"

#include "auxiliary/logger_implenent.h"
#include "Engine.h"

#define CONFIG_IMPLEMENT
#include "Config.h"
#undef CONFIG_IMPLEMENT


Config config;


int main (int argc, char *args[]) {
	logger.write ("Mens et Manus " VERSION);

	config.load ();

	Engine engine;
	engine.mainLoop ();

	return 0;
}
