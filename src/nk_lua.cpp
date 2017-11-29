#include "nk_lua.h"


namespace lua::nk {

#define addBindNkFunc(name) {#name, name}
#define addExportNkKey(key) {#key, (int) key}


	void init (lua_State *L, nk_context *nkContext) {
		lua::nk::ctx = nkContext;

		// Bind functions
		luaL_Reg funclist[] = {
				addBindNkFunc (begin),
				addBindNkFunc (layout_row_static),
				addBindNkFunc (button_label),
				addBindNkFunc (_end),
				{NULL, NULL}
		};
		luaL_newlib (L, funclist);

		// Export constants
		field<int> keys[] = {
				addExportNkKey (NK_WINDOW_BORDER),
				addExportNkKey (NK_WINDOW_MOVABLE),
				addExportNkKey (NK_WINDOW_SCALABLE),
				addExportNkKey (NK_WINDOW_CLOSABLE),
				addExportNkKey (NK_WINDOW_MINIMIZABLE),
				addExportNkKey (NK_WINDOW_NO_SCROLLBAR),
				addExportNkKey (NK_WINDOW_TITLE),
				addExportNkKey (NK_WINDOW_SCROLL_AUTO_HIDE),
				addExportNkKey (NK_WINDOW_BACKGROUND),
				addExportNkKey (NK_WINDOW_SCALE_LEFT),
				addExportNkKey (NK_WINDOW_NO_INPUT),
				{NULL, 0}
		};
		setTableFields (L, keys);
		lua_setglobal (L, "gui");
	}


#undef addBindNkFunc
#undef addExportNkKey


	// Binded functions

	int begin (lua_State *L) {
		lua_pushboolean (L, nk_begin (lua::nk::ctx, luaL_checkstring (L, 1),
		                              nk_rect ((float) luaL_checknumber (L, 2),
		                                       (float) luaL_checknumber (L, 3),
		                                       (float) luaL_checknumber (L, 4),
		                                       (float) luaL_checknumber (L, 5)),
		                              (nk_flags) luaL_checkinteger (L, 6)));
		return 1;
	}


	int layout_row_static (lua_State *L) {
		nk_layout_row_static (lua::nk::ctx,
		                      (float) luaL_checknumber (L, 1),
		                      (int) luaL_checkinteger (L, 2),
		                      (int) luaL_checkinteger (L, 3));
		return 0;
	}


	int button_label (lua_State *L) {
		lua_pushboolean (L, nk_button_label (lua::nk::ctx, luaL_checkstring (L, 1)));
		return 1;
	}


	int _end (lua_State *L) {
		nk_end (lua::nk::ctx);
		return 0;
	}

}
