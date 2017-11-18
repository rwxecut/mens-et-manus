#pragma once

#include "nuklear/nuklear_common.h"
#include "lua_overlay.h"

namespace lua::nk {

	static nk_context *ctx;

	void init (lua_State *L, nk_context *nkContext);

	// Binded functions
	int begin (lua_State *L);
	int layout_row_static (lua_State *L);
	int button_label (lua_State *L);
	int end (lua_State *L);
}
