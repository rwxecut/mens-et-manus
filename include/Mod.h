#pragma once

#include <string>
#include <map>
#include <vector>
#include "Config.h"
#include "Logger.h"
#include "auxiliary/filesystem.h"


namespace Mod {
	typedef std::map<const char *, std::string> info_t;
	typedef std::vector<info_t> info_vector;
};


class ModList {
	Mod::info_t loadModInfo (LuaFile &file);

public:
	Mod::info_vector list;

	void load ();
	void clear ();
};
