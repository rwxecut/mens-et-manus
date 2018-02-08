#pragma once

#include "LuaFile.h"
#include "nuklear/nuklear_common.h"
#include "lua_overlay.h"

namespace lua::nk {
	void init (LuaFile *LF);
	void run (LuaFile *LF, nk_context *nkContext);

	// Binded functions
	lua_cfunc (begin);
	lua_cfunc (layout_row_dynamic);
	lua_cfunc (layout_row_static);
	lua_cfunc (button_label);
	lua_cfunc (finish);
}
