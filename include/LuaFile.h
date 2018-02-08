#pragma once

#include "auxiliary/lua_overlay.h"
#include "auxiliary/errors.h"


class LuaFile {
	const char *filename;

public:
	lua_State *L;
	LuaFile (const char *filename);
	~LuaFile ();

	void run();
};