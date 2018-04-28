#include "LuaFile.h"


LuaFile::LuaFile (const char *filename) {
	this->filename = filename;
	state.open_libraries ();
	state.script_file (filename);
	/*int errcode = 0;
	if ((errcode = luaL_loadfile (L, filename))) {
		const char *msg = lua_tostring (L, -1);
		fatalError ("Error while loading Lua file %s (error code %d):\n%s",
		            filename, errcode, msg);
	}*/
	logger.write ("Lua file loaded: %s", filename);
};
