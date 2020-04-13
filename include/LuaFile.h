#pragma once

#define SOL_CHECK_ARGUMENTS 1

#include <string>
#include "lib/sol.hpp"


class LuaFile {
	std::string filename;

public:

	sol::state state;

	LuaFile (std::string const &filename, uint8_t flags);
	void call (const char *funcname);

	static constexpr uint8_t BIND_NOTHING = 0;
	static constexpr uint8_t BIND_GAME     = 1 << 0;
	static constexpr uint8_t BIND_GUI      = 1 << 1;
	static constexpr uint8_t BIND_MODLIST  = 1 << 2;
};
