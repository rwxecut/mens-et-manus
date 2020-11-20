#pragma once

#include <string>
#include <map>
#include <vector>
#include "engine/LuaFile.h"


namespace Mod {
	typedef std::map<const char *, std::string> info_t;
	typedef std::vector<info_t> info_vector;

	class List {
		static info_t loadModInfo (lua::File &file);

	public:
		info_vector list;

		void load ();
		void clear ();
	};
}
