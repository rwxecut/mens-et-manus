#include "lua_binders/modlist_lua.h"


namespace lua {
	namespace bind {

		Modlist::Modlist (File *LF, ModList *modList) : LF (LF), mList (modList) {
			// Usertype for mods list bindings should not be directly used in scripts
			auto mods = LF->state.new_usertype<Modlist> ("__ModsBindingType");
			/*---------- Export functions ----------*/
			#define MODLIST_EXPORT_METHOD(field) {mods[#field] = &Modlist::field;}
			MODLIST_EXPORT_METHOD (getList);
			#undef MODLIST_EXPORT_METHOD
		}


		/*---------- Binded functions ----------*/

		sol::nested<Mod::info_vector> Modlist::getList () {
			return sol::nested<Mod::info_vector> (mList->list);
		}

	}
}
