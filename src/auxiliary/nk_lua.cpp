#include "auxiliary/nk_lua.h"


namespace lua::nk {

	void init (lua_State *L) {
		// Bind functions
		luaL_Reg funclist[] = {
				lua_addBindFunc (begin),
				lua_addBindFunc (layout_row_static),
				lua_addBindFunc (button_label),
				lua_addBindFunc (_end),
				{NULL, NULL}
		};
		luaL_newlib (L, funclist);

		// Export constants
		field<int> keys[] = {
				lua_addExportKey (NK_WINDOW_BORDER),
				lua_addExportKey (NK_WINDOW_MOVABLE),
				lua_addExportKey (NK_WINDOW_SCALABLE),
				lua_addExportKey (NK_WINDOW_CLOSABLE),
				lua_addExportKey (NK_WINDOW_MINIMIZABLE),
				lua_addExportKey (NK_WINDOW_NO_SCROLLBAR),
				lua_addExportKey (NK_WINDOW_TITLE),
				lua_addExportKey (NK_WINDOW_SCROLL_AUTO_HIDE),
				lua_addExportKey (NK_WINDOW_BACKGROUND),
				lua_addExportKey (NK_WINDOW_SCALE_LEFT),
				lua_addExportKey (NK_WINDOW_NO_INPUT),
				{NULL, 0}
		};
		setTableFields (L, keys);
		lua_setglobal (L, "gui");
	}


	void run (lua_State *L, nk_context *nkContext, const char *filename) {
		lua::nk::ctx = nkContext;
		luaL_dofile (L, filename);
	}


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
