#pragma once

#define SOL_CHECK_ARGUMENTS 1

#include <string>
#include "lib/sol.hpp"


class LuaFile {
	std::string filename;

public:

	sol::state state;

	LuaFile (std::string const &filename);
	void call (const char *funcname);
};
