#include "lua_binders/modlist_lua.h"


namespace lua {
	ModlistBinding::ModlistBinding (LuaFile *LF, ModList *modList) : LF(LF), mList(modList) {
		// Usertype for mods bindings should not be directly used in scripts
		auto mods = LF->state.new_usertype<lua::ModlistBinding> ("__ModsType");
		/*---------- Export functions ----------*/
		#define MODS_ADD_FIELD(field) {mods[#field] = &ModlistBinding::field;}
		MODS_ADD_FIELD (getList);
		#undef MODS_ADD_FIELD
	}

	/*---------- Binded functions ----------*/

	sol::nested<Mod::info_vector> ModlistBinding::getList () {
		return sol::nested<Mod::info_vector> (mList->list);
	}
}
