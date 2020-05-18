#pragma once

#include "Mod.h"
#include "LuaFile.h"

namespace lua {
	namespace bind {

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
}
