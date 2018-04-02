#pragma once

#include "auxiliary/lua_overlay.h"
#include "auxiliary/errors.h"


enum class Scope {
	global, tableField
};


class LuaFile {
	const char *filename;


	//@formatter:off
	int __getValueTyped (int) { return (int) luaL_checkinteger (L, -1); }
	double __getValueTyped (double) { return (double) luaL_checknumber (L, -1); }
	char * __getValueTyped (char *) { return (char *) luaL_checkstring (L, -1); }
	//@formatter:on

public:

	lua_State *L;

	LuaFile (const char *filename);
	~LuaFile ();

	// Null to execute the global
	void run (const char *func = NULL);


	template<typename T>
	T getValue (const char *name, Scope scope) {
		if (scope == Scope::global)
			lua_getglobal (L, name);
		if (scope == Scope::tableField)
			lua_getfield (L, -1, name);
		T value = __getValueTyped (value);
		lua_pop(L, 1);
		return value;
	}
};
