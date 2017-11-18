#include "nk_lua.h"


namespace lua::nk {

	void init (lua_State *L, nk_context *nkContext) {
		lua::nk::ctx = nkContext;
		luaL_Reg funclist[] = {
				{"begin",             lua::nk::begin},
				{"layout_row_static", lua::nk::layout_row_static},
				{"button_label",      lua::nk::button_label},
				{"_end",              lua::nk::end},
				{NULL, NULL}
		};
		luaL_newlib (L, funclist);
		lua_setglobal (L, "gui");
	}

	// Binded functions

	int begin (lua_State *L) {
		const char *name = luaL_checkstring (L, 1);
		struct {
			float x, y, w, h;
		} rect = {(float) luaL_checknumber (L, 2),
		          (float) luaL_checknumber (L, 3),
		          (float) luaL_checknumber (L, 4),
		          (float) luaL_checknumber (L, 5)};
		lua_pushboolean (L, nk_begin (lua::nk::ctx, name, nk_rect (rect.x, rect.y, rect.w, rect.h), NK_WINDOW_BORDER));
		return 1;
	}


	int layout_row_static (lua_State *L) {
		struct {
			float h;
			int iw, cols;
		} row = {(float) luaL_checknumber (L, 1),
		         (int) luaL_checkinteger (L, 2),
		         (int) luaL_checkinteger (L, 3)};
		nk_layout_row_static (lua::nk::ctx, row.h, row.iw, row.cols);
		return 0;
	}


	int button_label (lua_State *L) {
		const char *name = luaL_checkstring (L, 1);
		lua_pushboolean (L, nk_button_label (lua::nk::ctx, name));
		return 1;
	}


	int end (lua_State *L) {
		nk_end (lua::nk::ctx);
		return 0;
	}

}
