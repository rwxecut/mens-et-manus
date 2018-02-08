#include "Config.h"

#define CONFIG_PATH "../assets/config.lua"


Config::Config () {
	logger.write ("Loading config");
	LuaFile *conf = new LuaFile (CONFIG_PATH);
	conf->run ();

	lua_getglobal (conf->L, "screen");
	screen.width = lua::getTableField<int> (conf->L, "width");
	screen.height = lua::getTableField<int> (conf->L, "height");
	lua_pop (conf->L, 1);

	lua_getglobal (conf->L, "cam");
	cam.moveSpeedMax = (GLdouble) lua::getTableField<double> (conf->L, "moveSpeedMax");
	cam.moveAcceleration = (GLdouble) lua::getTableField<double> (conf->L, "moveAcceleration");
	cam.zoomSpeed = (GLdouble) lua::getTableField<double> (conf->L, "zoomSpeed");
	lua_pop (conf->L, 1);

	lua_getglobal (conf->L, "fpsInterval");
	fpsInterval = luaL_checknumber (conf->L, -1);
	lua_pop (conf->L, 1);

	delete conf;
}
