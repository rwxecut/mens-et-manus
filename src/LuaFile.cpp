#include "LuaFile.h"
#include "Logger.h"
#include "lua_binders/game_lua.h"
#include "lua_binders/nk_lua.h"
#include "lua_binders/modlist_lua.h"
#include "auxiliary/errors.h"


LuaFile::LuaFile (std::string const &filename, uint8_t flags) {
	// Load file and create Lua state
	this->filename = filename;
	state.open_libraries ();
	try {
		state.safe_script_file (filename);
	}
	catch (const sol::error &e) {
		fatalError ("Error while executing Lua file %s: %s", filename.c_str(), e.what ());
	}
	logger.write ("Lua file loaded: %s", filename.c_str ());

	// Bind functions if needed
	if (flags & BIND_GAME) lua::game::bind (this);
	if (flags & BIND_GUI) lua::nk::bind (this);
	if (flags & BIND_MODLIST) lua::modlist::bind (this);
};


void LuaFile::call (const char *funcname) {
	sol::protected_function func = state[funcname];
	sol::protected_function_result result = func ();
	if (!result.valid ()) {
		sol::error err = result;
		fatalError ("Error while executing function '%s': %s", funcname, err.what ());
	}
}
