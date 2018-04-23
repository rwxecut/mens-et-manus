#include "Config.h"

#define CONFIG_PATH "../assets/config.lua"


Config::Config () {
	logger.write ("Loading config");
	LuaFile *conf = new LuaFile (CONFIG_PATH);
	conf->run ();

	lua_getglobal (conf->L, "screen");
	screen.width = conf->getValue<int> ("width", Scope::tableField);
	screen.height = conf->getValue<int> ("height", Scope::tableField);
	lua_pop (conf->L, 1);

	lua_getglobal (conf->L, "cam");
	cam.moveSpeedMax = conf->getValue<double> ("moveSpeedMax", Scope::tableField);
	cam.moveAcceleration = conf->getValue<double> ("moveAcceleration", Scope::tableField);
	cam.zoomSpeed = conf->getValue<double> ("zoomSpeed", Scope::tableField);
	lua_pop (conf->L, 1);

	fpsMeasureInterval = conf->getValue<double> ("fpsInterval", Scope::global);

	delete conf;
}
