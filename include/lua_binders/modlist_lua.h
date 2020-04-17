#pragma once

#include "Mod.h"
#include "LuaFile.h"

namespace lua {
	class ModlistBinding {
		LuaFile *LF;
		ModList *mList;
	public:
		ModlistBinding (LuaFile *LF, ModList *modList);

	/* Binded functions */
	private:
		sol::nested<Mod::info_vector> getList ();
	};
}
