#pragma once

#define SOL_CHECK_ARGUMENTS 1

#include <string>
#include "auxiliary/sol.hpp"
#include "auxiliary/errors.h"


class LuaFile {
	const char *filename;

public:

	sol::state state;

	LuaFile (const char *filename);
};
