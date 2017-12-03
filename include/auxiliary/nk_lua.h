#pragma once

#include "nuklear/nuklear_common.h"
#include "lua_overlay.h"

namespace lua::nk {

	static nk_context *ctx;

	void init (lua_State *L);
	void run (lua_State *L, nk_context *nkContext, const char *filename);

	// Binded functions
	int begin (lua_State *L);
	int layout_row_static (lua_State *L);
	int button_label (lua_State *L);
	int _end (lua_State *L);
}
