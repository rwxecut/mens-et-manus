#include "lua_binders/modlist_lua.h"
#include <vector>

#define MODS_ADD_FIELD(field) {mods[#field] = field;}

namespace lua::modlist {
	ModList *mList;


	void init (ModList *modList) {
		mList = modList;
	}


	// Binded functions

	sol::nested<Mod::info_vector> getList () {
		return sol::nested<Mod::info_vector> (mList->list);
	};


	// Bind functions
	void bind (LuaFile *LF) {
		sol::table mods = LF->state.create_named_table ("mods");
		/*---------- Export functions ----------*/
		MODS_ADD_FIELD (getList);
	}
}