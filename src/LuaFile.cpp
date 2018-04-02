#include "LuaFile.h"


LuaFile::LuaFile (const char *filename) {
	this->filename = filename;
	int errcode = 0;
	if (!(L = luaL_newstate ()))
		fatalError ("Error while loading Lua file %s: can't create Lua state", filename);
	luaL_openlibs (L);
	if ((errcode = luaL_loadfile (L, filename))) {
		const char *msg = lua_tostring (L, -1);
		fatalError ("Error while loading Lua file %s (error code %d):\n%s",
		            filename, errcode, msg);
	}
	logger.write ("Lua file loaded: %s", filename);
};


LuaFile::~LuaFile () {
	lua_pop (L, 1);
	lua_close (L);
};


void LuaFile::run (const char *func) {
	if (func)
		lua_getglobal (L, func);
	else
		lua_pushvalue (L, -1);
	int errcode = 0;
	if ((errcode = lua_pcall (L, 0, LUA_MULTRET, 0))) {
		const char *msg = lua_tostring (L, -1);
		fatalError ("Error while executing Lua file %s (error code %d):\n%s",
		            filename, errcode, msg);
	}
};
