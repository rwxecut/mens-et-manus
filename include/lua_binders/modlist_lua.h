#pragma once

#include "Mod.h"
#include "LuaFile.h"

namespace lua {
	namespace bind {

		// TODO: name differs only case of 1 letter from ModList umu
		class Modlist {
			LuaFile *LF;
			ModList *mList;
		public:
			Modlist (LuaFile *LF, ModList *modList);

			/* Binded functions */
		private:
			sol::nested<Mod::info_vector> getList ();
		};

	}
}
