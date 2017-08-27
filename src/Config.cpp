#include <Config.h>
#include "Config.h"

#define CONFIG_PATH "../assets/config.lua"

Config::Config () {
	lua_State *L = luaL_newstate ();
	luaL_openlibs (L);
	if (luaL_loadfile (L, CONFIG_PATH) || lua_pcall (L, 0, 0, 0))
		throw lua::LuaError ("Error while loading config.lua");

	lua_getglobal (L, "screen");
	screen.width = lua::getTableField<int> (L, "width");
	screen.height = lua::getTableField<int> (L, "height");
	lua_pop (L, 1);

	lua_getglobal (L, "cam");
	cam.moveSpeedMax = (GLdouble) lua::getTableField<double> (L, "moveSpeedMax");
	cam.moveAcceleration = (GLdouble) lua::getTableField<double> (L, "moveAcceleration");
	cam.zoomSpeed = (GLdouble) lua::getTableField<double> (L, "zoomSpeed");
	lua_pop (L, 1);

	lua_close (L);
}
