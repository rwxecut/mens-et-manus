#include "LuaFile.h"


LuaFile::LuaFile (const char *filename) {
	this->filename = filename;
	L = luaL_newstate ();
	luaL_openlibs (L);
	if (luaL_loadfile (L, filename))
		fatalError ("Error while loading %s", filename);
	logger.write ("Lua file loaded: %s", filename);
};


LuaFile::~LuaFile () {
	lua_pop (L, 1);
	lua_close (L);
};


void LuaFile::run () {
	lua_pushvalue (L, -1);
	int errcode = 0;
	if ((errcode = lua_pcall (L, 0, LUA_MULTRET, 0))) {
		const char *msg = lua_tostring (L, -1);
		fatalError ("Error while executing Lua file %s (error code %d):\n%s",
		            filename, errcode, msg);
	}
};
