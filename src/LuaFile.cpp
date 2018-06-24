#include "LuaFile.h"


LuaFile::LuaFile (std::string const &filename) {
	this->filename = filename;
	state.open_libraries ();
	try {
		state.safe_script_file (filename);
	}
	catch (const sol::error &e) {
		fatalError ("Error while executing Lua file %s: %s", filename, e.what ());
	}
	logger.write ("Lua file loaded: %s", filename.c_str ());
};


void LuaFile::call (const char *funcname) {
	sol::protected_function func = state[funcname];
	sol::protected_function_result result = func ();
	if (!result.valid ()) {
		sol::error err = result;
		fatalError ("Error while executing function '%s': %s", funcname, err.what ());
	}
}
