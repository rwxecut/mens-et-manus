#include "Config.h"

#define CONFIG_PATH "../assets/config.lua"

Config::Config () {
	lua_State *L = luaL_newstate ();
	luaL_openlibs (L);
	if (luaL_loadfile (L, CONFIG_PATH) || lua_pcall (L, 0, 0, 0))
		throw lua::LuaError ("Error while loading config.lua");

	lua_getglobal (L, "screen");
	lua_pushstring (L, "width");
	lua_gettable (L, -2);
	config.screen.width = (int) lua_tointeger (L, -1);
	lua_pop (L, 1);
	lua_pushstring (L, "height");
	lua_gettable (L, -2);
	config.screen.height = (int) lua_tointeger (L, -1);
	lua_pop (L, 2);

	lua_getglobal (L, "cam");
	lua_pushstring (L, "FOV");
	lua_gettable (L, -2);
	config.cam.FOV = (GLdouble) lua_tonumber (L, -1);
	lua_pop (L, 2);

	lua_close (L);
}
