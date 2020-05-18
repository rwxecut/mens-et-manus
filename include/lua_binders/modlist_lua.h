#pragma once

#include "Mod.h"
#include "LuaFile.h"

namespace lua::bind {
	class Modlist {
		File *LF;
		Mod::List *mList;
	public:
		Modlist (File *LF, Mod::List *modList);

	/* Binded functions */
	private:
		sol::nested<Mod::info_vector> getList ();
	};
}
