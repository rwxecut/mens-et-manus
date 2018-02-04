#pragma once

#include "nuklear/nuklear_common.h"
#include "lua_overlay.h"

namespace lua::nk {
	void init (lua_State *L);
	void run (lua_State *L, nk_context *nkContext, const char *filename);

	// Binded functions
	lua_cfunc (begin);
	lua_cfunc (layout_row_dynamic);
	lua_cfunc (layout_row_static);
	lua_cfunc (button_label);
	lua_cfunc (finish);
}
