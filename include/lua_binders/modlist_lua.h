#pragma once

#include "lua_binders/bind_lua.h"
#include "engine/Mod.h"

namespace lua::bind {
	class Modlist : public Bind {
		Mod::List *mList;

	public:
		Modlist (File *LF, Mod::List *modList);

	/* Binded functions */
	private:
		sol::nested<Mod::info_vector> getList ();
	};
}
